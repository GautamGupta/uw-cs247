#include <iostream>
#include "Collection.h"

using namespace std;

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
