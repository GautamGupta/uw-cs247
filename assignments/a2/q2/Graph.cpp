#include <iostream>
#include "Graph.h"

using namespace std;

Graph::BCodeNotFoundException::BCodeNotFoundException() {}

Graph::BCodeNotFoundException::BCodeNotFoundException(string code)
        : code_(code) {}

string Graph::BCodeNotFoundException::code() const {
    return code_;
}

Graph::SelfConnectException::SelfConnectException(string code)
        : code_(code) {}

string Graph::SelfConnectException::code() const {
    return code_;
}

Graph::NoEdgeException::NoEdgeException(string code, string code2)
        : code_(code), code2_(code2) {}

string Graph::NoEdgeException::code() const {
    return code_;
}

string Graph::NoEdgeException::code2() const {
    return code2_;
}

Graph::EdgeExistsException::EdgeExistsException(string code, string code2)
        : code_(code), code2_(code2) {}

string Graph::EdgeExistsException::code() const {
    return code_;
}

string Graph::EdgeExistsException::code2() const {
    return code2_;
}

Graph::InvalidConnectorTypeException::InvalidConnectorTypeException(string type)
        : type_(type) {}

string Graph::InvalidConnectorTypeException::type() const {
    return type_;
}

Graph::Graph() :
        _node(NULL) {}

Graph::~Graph() {
    deleteGraph();
}

Graph::Graph(const Graph &g) {
    *this = g;
}

/**
 * @return Graph::Node* Buildings Node (Linked List)
 */
Building* Graph::findBuilding(string code) const {
    Graph::Node *node = findNode(code);
    if (node != NULL) {
        return node->building;
    }

    return NULL;
}

void Graph::addNode(Building* building) {
    if (building == NULL) {
        throw BCodeNotFoundException();
    }

    Node *new_node = new Node(building, NULL, NULL);

    // Insert in a sorted list
    if (_node == NULL) {
        _node = new_node;
    } else {
        Node *node = nodes();
        while (node->next != NULL && node->next->building->code() < new_node->building->code()) {
            node = node->next;
        }
        new_node->next = node->next;
        node->next = new_node;
    }
}

void Graph::removeNode(string code) {
    Graph::Node *node = nodes();
    bool found = false;

    if (node != NULL) { // no nodes

        if (node->building->code() == code) { // head node
            _node = deleteNode(node);
            found = true;
        } else { // further nodes
            while (node->next != NULL) {
                if (node->next->building->code() == code) {
                    node->next = deleteNode(node->next);
                    found = true;
                    break;
                }
                node = node->next;
            }
        }

    }

    if (!found) {
        throw BCodeNotFoundException();
    }
}

void Graph::addEdge(string b1_code, string b2_code, string type) {
    Node *node1 = findNode(b1_code);
    Node *node2 = findNode(b2_code);
    if (node1 == NULL) {
        throw BCodeNotFoundException(b1_code);
    } else if (node2 == NULL) {
        throw BCodeNotFoundException(b2_code);
    } else if (node1 == node2) {
        throw SelfConnectException(b2_code);
    } else if (type != "bridge" && type != "tunnel" && type != "hall") {
        throw InvalidConnectorTypeException(type);
    } else if (areConnected(node1, node2)) {
        throw EdgeExistsException(b1_code, b2_code);
    }

    addConnector(node1, node2, type);
    addConnector(node2, node1, type);
}

void Graph::removeEdge(string b1_code, string b2_code) {
    Node *node1 = findNode(b1_code);
    Node *node2 = findNode(b2_code);
    if (node1 == NULL) {
        throw BCodeNotFoundException(b1_code);
    } else if (node2 == NULL) {
        throw BCodeNotFoundException(b2_code);
    }

    removeEdge(node1, node2);
}

void Graph::removeEdge(Node *node1, Node *node2) {
    if (node1 == NULL || node2 == NULL
            || node1->building == NULL || node2->building == NULL) {
        return;
    }

    deleteConnector(node1, node2->building->code());
    deleteConnector(node2, node1->building->code());
}

void Graph::printPaths(string b1_code, string b2_code, const bool all) const {
    Node *node1 = findNode(b1_code);
    Node *node2 = findNode(b2_code);
    if (node1 == NULL) {
        throw BCodeNotFoundException(b1_code);
    } else if (node2 == NULL) {
        throw BCodeNotFoundException(b2_code);
    }
}

void Graph::deleteGraph() {
    while (_node != NULL) {
        _node = deleteNode(_node);
    }
}

Graph::Node* Graph::findNode(string code) const {
    Graph::Node *node = nodes();
    while (node != NULL) {
        if (node->building->code() == code) {
            return node;
        }
        node = node->next;
    }

    return NULL;
}

Graph::Node* Graph::deleteNode(Graph::Node *node) {
    if (node == NULL) {
        return NULL;
    }

    Graph::Node *next = node->next;

    while (node->connector != NULL) {
        // cout << "delCon" << (node->connector->next != NULL) << endl;
        Connector *next = node->connector->next;
        removeEdge(node, node->connector->node);
        node->connector = next;
    }

    delete node;

    return next;
}

void Graph::addConnector(Node *from, Node *to, string type) {
    Connector *connector = new Connector(to, from->connector, type);
    from->connector      = connector;
}

/**
 * This doesn't take care of deleting the counterpath connector.
 * Use removeEdge() instead.
 *
 * @return Graph::Connector* The next connector
 */
void Graph::deleteConnector(Node *node, BCode connected_code) {
    bool found = false;

    if (node != NULL && node->connector != NULL) {
        if (node->connector->node->building->code() == connected_code) { // head
            delete node->connector;
            node->connector = NULL;
            found = true;
        } else { // further
            Graph::Connector* connector = node->connector;
            while (connector->next != NULL) {
                if (connector->next->node->building->code() == connected_code) {
                    Graph::Connector* next = connector->next->next;
                    delete connector->next;
                    connector->next = next;
                    found = true;
                    break;
                }
                connector = connector->next;
            }
        }
    }

    if (!found) {
        throw NoEdgeException(node->building->code().code(), connected_code.code());
    }
}

/**
 * Check if an edge exists between two nodes
 */
bool Graph::areConnected(Node* node1, Node* node2) {
    Graph::Connector* connector = node1->connector;
    while (connector != NULL) {
        if (connector->node->building->code() == node2->building->code()) {
            return true;
        }
    }

    return false;
}

/**
 * Compare if two nodes (including next*) are equal. Includes connectors.
 *
 * Nodes are sorted by code (ascending), so we don't need to worry about order.
 */
bool Graph::isNodeEqual(Node* node1, Node* node2) {
    if (node1 == NULL && node2 == NULL) { // both null = equal
        return true;
    } else if (node1 == NULL || node2 == NULL) { // one is null => not equal
        return false;
    }

    if (node1->building->code() != node2->building->code()
        || node1->building->name() != node2->building->name()) {
        return false;
    }

    Connector *connector1 = node1->connector;
    Connector *connector2 = node2->connector;
    int connector1_count = 0, connector2_count = 0;

    while (connector1 != NULL) {
        while (connector2 != NULL) {
            if (connector1->type == connector2->type
                && connector1->node->building->code() == connector2->node->building->code()
                && connector1->node->building->name() == connector2->node->building->name()) {
                break;
            } else {
                connector2 = connector2->next;
            }
        }

        // not found
        if (connector1 != NULL && connector2 == NULL) {
            return false;
        }

        connector1 = connector1->next;
        connector2 = node2->connector;
        connector1_count++;
    }

    // Can't do a count inside the previous loop for connector2
    while (connector2 != NULL) {
        connector2_count++;
        connector2 = connector2->next;
    }

    if (connector1_count != connector2_count) {
        return false;
    }

    if (node1->next != NULL && node2->next != NULL) { // go to the next node
        return isNodeEqual(node1->next, node2->next);
    } else if (node1->next != NULL || node2->next != NULL) { // one is not null = not equal
        return false;
    } else { // last node and is equal
        return true;
    }
}

/**
 * @return Graph::Node* Buildings Graph::Node (Linked List)
 */
Graph::Node* Graph::nodes() const {
    return _node;
}

ostream& operator<<(ostream &sout, const Graph &g) {
    Graph::Node *node = g.nodes();
    while (node != NULL) {
        // Building info
        cout << node->building->code() << "\t" << node->building->name() << endl;

        // Connectors
        Graph::Connector *connector = node->connector;
        if (connector != NULL) {
            cout << "\t" << "Connects to: ";
            while (connector != NULL) {
                cout << connector->node->building->code() << " (" << connector->type << ")";
                if (connector->next != NULL) {
                    cout << ", ";
                }
                connector = connector->next;
            }
            cout << endl;
        }

        cout << endl;
        node = node->next;
    }

    return sout;
}

Graph& Graph::operator=(const Graph &g) {
    // Why would you do this
    if (this == &g) {
        return *this;
    }

    // Clear
    deleteGraph();
    _node = NULL;

    Node *node1, *node2;

    // Add all nodes first
    node1 = g.nodes();
    while (node1 != NULL) {
        addNode(node1->building);
        node1 = node1->next;
    }

    // Add connectors
    node1 = g.nodes();
    node2 = nodes();
    while (node1 != NULL) {
        Connector *connector = node1->connector;
        while (connector != NULL) {
            addConnector(node2, findNode(connector->node->building->code().code()), connector->type);
            connector = connector->next;
        }

        node1 = node1->next;
        node2 = node2->next;
    }

    return *this;
}

bool Graph::operator==(const Graph &g) const {
    return isNodeEqual(_node, g.nodes());
}
