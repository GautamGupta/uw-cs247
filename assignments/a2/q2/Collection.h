#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include "Building.h"

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

#endif
