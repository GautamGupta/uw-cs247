#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//************************************************************************
//* YOUR IMPLENTATION OF BCODE, BUILDING, COLLECTION HERE
//************************************************************************

/** BCODE */

class BCode {
public:
    explicit BCode(const string);   /* Building code */
    string code() const;            /* Accessor -- string code */
    friend ostream& operator<<(ostream&, const BCode&);
    friend bool operator==(const BCode&, const string&);
    friend bool operator==(const BCode&, const BCode&);
    friend bool operator!=(const BCode&, const BCode&);
    friend bool operator<(const BCode&, const BCode&);
    friend bool operator>(const BCode&, const BCode&);

private:
    string _code;
};

/**
 * Converts a string into a building code after checking for requiremets
 */
BCode::BCode(const string code) {
    // length should be b/w 1-3 chars
    if (code.length() < 1 || code.length() > 3) {
        exit(1);
    }
    // all chars should be uppercase letters / numbers
    for (int i = 1; i < code.length(); ++i) {
        if (!isdigit(code[i]) && (!isalpha(code[i]) || !isupper(code[i]))) {
            exit(1);
        }
    }
    // first char should be a letter
    if (!isalpha(code[0])) {
        exit(1);
    }

    _code = code;
}

/**
 * @return string Building Code
 */
string BCode::code() const {
    return _code;
}

ostream& operator<<(ostream &sout, const BCode &code) {
    sout << code.code();
    return sout;
}

bool operator== (const BCode &a, const string &b) {
    return a.code().compare(b) == 0;
}

bool operator== (const BCode &a, const BCode &b) {
    return a == b.code();
}

bool operator!= (const BCode &a, const BCode &b) {
    return !(a == b);
}

bool operator< (const BCode &a, const BCode &b) {
    return a.code().compare(b.code()) < 0;
}

bool operator> (const BCode &a, const BCode &b) {
    return a.code().compare(b.code()) > 0;
}

/** BUILDING */

class Building {
public:
    explicit Building(const BCode, const string);
    explicit Building(const string, const string);
    BCode code() const;
    string name() const;
    friend ostream& operator<<(ostream&, const Building&);

private:
    BCode _code;
    string _name;
};

/**
 * Creates a new building
 */
Building::Building(const BCode code, const string name) :
        _code(code), _name(name) {}

/**
 * Creates a new building
 */
Building::Building(const string code, const string name) :
        _code(BCode(code)), _name(name) {}

/**
 * @return BCode Building Code
 */
BCode Building::code() const {
    return _code;
}

/**
 * @return string Official Building Name
 */
string Building::name() const {
    return _name;
}

ostream& operator<<(ostream &sout, const Building &building) {
    sout << building.code() << "\t" << building.name();
    return sout;
}

/** COLLECTION */

class Collection {
public:
    Collection();
    ~Collection();
    Building* findBuilding(string) const;
    void insert(string, string);
    void remove(string);

private:
    struct Node {
        Building *building;
        Node *next;

        Node(Building *building, Node *next) :
                building(building), next(next) {}
    };

    Node* nodes() const;
    Node* deleteNode(Node *node);

    Node *_node;
};

/**
 * Constructor
 */
Collection::Collection() :
        _node(NULL) {}

Collection::~Collection() {
    while (_node != NULL) {
        Collection::Node *next = _node->next;
        delete _node->building;
        delete _node;
        _node = next;
    }
}

/**
 * @return Collection::Node* Buildings Collection::Node (Linked List)
 */
Building* Collection::findBuilding(string code) const {
    Collection::Node *node = nodes();
    while (node != NULL) {
        if (node->building->code() == code) {
            return node->building;
        }
        node = node->next;
    }

    return NULL;
}

/**
 * @return Building Add a building to collection
 */
void Collection::insert(string code, string name) {
    Building *building = new Building(code, name);
    _node = new Collection::Node(building, nodes());
}

void Collection::remove(string code) {
    Collection::Node *node = nodes();

    if (node == NULL) { // no nodes
        return;
    }

    if (node->building->code() == code) { // head node
        _node = deleteNode(node);
    } else { // further nodes
        while (node->next != NULL) {
            if (node->next->building->code() == code) {
                node->next = deleteNode(node->next);
                break;
            }
            node = node->next;
        }
    }
}

/**
 * @return Collection::Node* Buildings Collection::Node (Linked List)
 */
Collection::Node* Collection::nodes() const {
    return _node;
}

Collection::Node* Collection::deleteNode(Collection::Node *node) {
    if (node == NULL) {
        return NULL;
    }

    Collection::Node *next = node->next;
    delete node;

    return next;
}

//===================================================================
// Graph (of Buildings and Connectors)
//===================================================================

class Graph {
public:
    Graph();                                                // constructor
    ~Graph();                                               // destructor
    Graph ( const Graph& );                                 // copy constructor
    void addNode ( Building* );                             // mutator - add node to graph
    void removeNode ( string );                             // mutator - remove node from graph
    Building* findBuilding ( string ) const;                // accessor - find building stored in node in graph
    void addEdge ( string, string, string );                // mutator - add edge to graph
    void removeEdge ( string, string );                     // mutator - remove edge from graph
    void printPaths ( string, string, const bool = false ) const; // accessor - print path from one node to another
    void deleteGraph();                                     // delete graph
    friend ostream& operator<< ( ostream&, const Graph& );  // insertion operator (insert graph into output stream)
    Graph& operator= ( const Graph& );                      // assignment operator for graph objects
    bool operator== ( const Graph& ) const;                 // equality operator for graph objects

private:

    struct Node; // used by Connector

    struct Connector {
        Node *node;
        Connector *next;
        string type;

        Connector(Node *node, Connector *next, string type) :
                node(node), next(next), type(type) {}
    };

    struct Node {
        Building *building;
        Node *next;
        Connector *connector;

        Node(Building *building, Node *next, Connector *connector) :
                building(building), next(next), connector(connector) {}
    };

    void removeEdge(Node*, Node*);
    Node* findNode(string) const;
    Node* deleteNode(Node*);
    void addConnector(Node*, Node*, string);
    void deleteConnector(Node*, BCode);
    bool static isNodeEqual(Node*, Node*);

    Node* nodes() const;
    Node *_node;

};

//************************************************************************
//* YOUR IMPLENTATION OF GRAPH HERE
//************************************************************************

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
        return;
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

    if (node == NULL) { // no nodes
        return;
    }

    if (node->building->code() == code) { // head node
        _node = deleteNode(node);
    } else { // further nodes
        while (node->next != NULL) {
            if (node->next->building->code() == code) {
                node->next = deleteNode(node->next);
                break;
            }
            node = node->next;
        }
    }
}

void Graph::addEdge(string b1_code, string b2_code, string type) {
    Node *node1 = findNode(b1_code);
    Node *node2 = findNode(b2_code);
    if (node1 == NULL || node2 == NULL) {
        return;
    }

    addConnector(node1, node2, type);
    addConnector(node2, node1, type);
}

void Graph::removeEdge(string b1_code, string b2_code) {
    Node *node1 = findNode(b1_code);
    Node *node2 = findNode(b2_code);
    if (node1 == NULL || node2 == NULL) {
        return;
    }

    removeEdge(node1, node2);
}

void Graph::removeEdge(Node *node1, Node *node2) {
    deleteConnector(node1, node2->building->code());
    deleteConnector(node2, node1->building->code());
}

void Graph::printPaths(string b1_code, string b2_code, const bool all) const {

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

    cout << "delNode " << (node->connector != NULL) << endl;

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
    if (node == NULL || node->connector == NULL) {
        return;
    }

    cout << node->building->code() << " del " <<  connected_code.code() << endl;

    if (node->connector->node->building->code() == connected_code) { // head
        delete node->connector;
        node->connector = NULL;
    } else { // further
        Graph::Connector* connector = node->connector;
        while (connector->next != NULL) {
            if (connector->next->node->building->code() == connected_code) {
                Graph::Connector* next = connector->next->next;
                delete connector->next;
                connector->next = next;
                break;
            }
            connector = connector->next;
        }
    }
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

//************************************************************************
//  Test Harness Helper functions
//************************************************************************

//  test-harness operators
enum Op { NONE, mapPtr, building, wreckage, findB, node, remNode, edge, remEdge, delGraph, copyGraph, assignGraph, eq, path, print };

Op convertOp( string opStr ) {
    switch( opStr[0] ) {
        case 'm': return mapPtr;
        case 'b': return building;
        case 'w': return wreckage;
        case 'f': return findB;
        case 'n': return node;
        case 'v': return remNode;
        case 'e': return edge;
        case 'r': return remEdge;
        case 'd': return delGraph;
        case 'c': return copyGraph;
        case 'a': return assignGraph;
        case 'q': return eq;
        case 'p': return path;
        case 'g': return print;
        default: {
            return NONE;
        }
    }
}

//******************************************************************
// Test Harness for Graph ADT
//******************************************************************

int main( int argc, char *argv[] ) {
    Collection buildings;
    Graph map1, map2;

    // initialize buildings and map1 with input file, if present
    if ( argc > 1 ) {

        ifstream source(argv[1]);
        if ( source.fail() ) {
            cerr << "Error: Could not open file \"" << argv[1] << "\"." << endl;
            return 1;
        }

        // create a collection of buildings, and a map of buildings and interior links

        string type;
        source >> type;
        Op op = convertOp ( type );
        while ( !source.eof() ) {
            switch (op) {

                    // add a new building to the collection of Buildings, and add the building to map1
                case building : {
                    string code;
                    string name;
                    string name2;
                    source >> code >> name;
                    getline( source, name2 );
                    buildings.insert( code, name+name2 );
                    map1.addNode( buildings.findBuilding ( code ) );
                    break;
                }

                    // add a new link between two existing nodes in map1
                case edge: {
                    string code1, code2, type;
                    source >> code1 >> code2 >> type;
                    map1.addEdge( code1, code2, type );
                    string junk;
                    getline ( source, junk );
                    break;
                }

                default: { }
            }
            source >> type;
            op = convertOp( type );
        }
    }

    cout << map1;

    Graph* map = &map1;  // input commands affect which ever graph that map points to (map1 or map2)

    cout << "Test harness for Graph ADT:" << endl << endl;

    // get input command
    cout << "Command: ";
    string command;
    cin >> command;

    Op op = convertOp( command );

    while ( !cin.eof() ) {
        switch (op) {

                // set variable map to point to new graph (map1 or map2)
            case mapPtr: {
                string mapNo;
                cin >> mapNo;
                map = ( mapNo[0] == '1' ) ? &map1 : &map2;
                break;
            }

                // print the current map to the console
            case print: {
                cout << *map;
                break;
            }

                // add a new building to the collection of buildings
            case building : {
                string code;
                string name;
                string name2;
                cin >> code >> name;
                getline( cin, name2 );
                buildings.insert( code, name+name2 );
                break;
            }

                // add an existing building to the current map
            case node: {
                string code;
                cin >> code;
                map->addNode( buildings.findBuilding( code ) );
                string junk;
                getline( cin, junk );
                break;
            }

                // find a building in the current map
            case findB: {
                string code;
                cin >> code;
                Building *b = map->findBuilding ( code );
                if ( b ) {
                    cout << *b << endl;
                }
                else {
                    cout << "Couldn't find building " << code << endl;
                }
                cout << endl;
                string junk;
                getline( cin, junk );
                break;
            }

                // add a new link between existing graph nodes in the current map
            case edge: {
                string code1, code2, type;
                cin >> code1 >> code2 >> type;
                map->addEdge( code1, code2, type );
                string junk;
                getline ( cin, junk );
                break;
            }


                // delete the entire graph (no memory leak).  There is no change to the collection of Buildings.
            case delGraph: {
                map->deleteGraph();
                break;
            }

                // remove an existing edge from the current map
            case remEdge: {
                string code1, code2;
                cin >> code1 >> code2;
                map->removeEdge( code1, code2 );
                string junk;
                getline ( cin, junk );
                break;
            }

                // remove an existing node from the current map.  There is no change to the collection of Buildings.
            case remNode: {
                string code;
                cin >> code;
                map->removeNode( code );
                string junk;
                getline( cin, junk );
                break;
            }

                // remove an existing building from the collection of buildings.  The building also needs to be removed from the two maps, as well as all links involving the building
            case wreckage: {
                string code;
                cin >> code;
                map1.removeNode( code );
                map2.removeNode( code );
                buildings.remove ( code );
                string junk;
                getline ( cin, junk );
                break;
            }

                // check whether map1 is equal to map2
            case eq: {
                if ( map1 == map2 ) {
                    cout << "Maps 1 and 2 are equal." << endl;
                }
                else {
                    cout << "Maps 1 and 2 are NOT equal." << endl;
                }
                break;
            }

                // graph copy constructor
            case copyGraph: {
                Graph map3( *map );
                cout << map3;
                string junk;
                getline( cin, junk );
                break;
            }

                // graph assignment operator
            case assignGraph: {
                map1 = map2;
                cout << map1;
                break;
            }

                // find path(s) in graph from one building to another building
            case path: {
                string code1, code2, all;
                cin >> code1 >> code2 >> all;
                cout << "Paths from " << code1 << " to " << code2 << " are: " << endl;
                bool printall = ( all.length() > 0 && all.at(0) == 't' ) ? true : false;
                map->printPaths( code1, code2, printall );
                string junk;
                getline( cin, junk );
                break;
            }

            default: {
                cerr << "Invalid command." << endl;
            }
        }

        cout << "Command: ";
        cin >> command;
        op = convertOp( command );

    } // while cin OK

}
