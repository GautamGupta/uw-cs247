#include <iostream>
#include <vector>
#include "Collection.h"

using namespace std;

Collection::BCodeNotFoundException::BCodeNotFoundException(string code)
        : BCode::BCodeException(code) {}

void Collection::BCodeNotFoundException::printError() const {
    cout << endl << "ERROR: There is no building with the code \"" << code() << "\"." << endl;
}

Collection::BCodeExistsException::BCodeExistsException(string code)
        : BCode::BCodeException(code) {}

void Collection::BCodeExistsException::printError() const {
    cout << endl << "ERROR: Building Code \"" << code() << "\" is already in use." << endl;
}

Collection::BCodeExistedException::BCodeExistedException(string code)
        : BCode::BCodeException(code) {}

void Collection::BCodeExistedException::printError() const {
    cout << endl << "ERROR: Building Code \"" << code() << "\" was used for a former building." << endl;
}

/**
 * Constructor
 */
Collection::Collection() :
        _node(NULL) {}

Collection::~Collection() {
    // Delete Nodes
    while (_node != NULL) {
        Collection::Node *next = _node->next;
        delete _node->building;
        delete _node;
        _node = next;
    }

    // Delete wrecked buildings
    for (vector<Building*>::iterator it = wreckedBuildings.begin(); it != wreckedBuildings.end(); it++) {
        delete *it;
        it = wreckedBuildings.erase(it);
    }
}

/**
 * @return Building* Buildings Collection::Node (Linked List)
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
 * @return Building* Find a wrecked building
 */
Building* Collection::findWreckedBuilding(string code) {
    for (vector<Building*>::const_iterator it = wreckedBuildings.begin(); it < wreckedBuildings.end(); it++) {
        if ((*it)->code() == code) {
            return *it;
        }
    }

    return NULL;
}

/**
 * @return Building Add a building to collection
 */
void Collection::insert(string code, string name) {
    if (findBuilding(code) != NULL) {
        throw BCodeExistsException(code);
    } else if (findWreckedBuilding(code) != NULL) {
        throw BCodeExistedException(code);
    }

    Building *building = new Building(code, name);
    _node = new Collection::Node(building, nodes());
}

void Collection::remove(string code) {
    Collection::Node *node = nodes();
    Building *building;
    bool found = false;

    if (node != NULL) { // no nodes

        if (node->building->code() == code) { // head node
            building = node->building;
            _node = deleteNode(node);
            found = true;
        } else { // further nodes
            while (node->next != NULL) {
                if (node->next->building->code() == code) {
                    building = node->next->building;
                    node->next = deleteNode(node->next);
                    found = true;
                    break;
                }
                node = node->next;
            }
        }

    }

    if (!found) {
        throw BCodeNotFoundException(code);
    } else {
        wreckedBuildings.push_back(building);
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
