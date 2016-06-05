#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include "Building.h"

class Collection {
public:
    Collection();
    ~Collection();
    Building* findBuilding(std::string) const;
    void insert(std::string, std::string);
    void remove(std::string);

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
