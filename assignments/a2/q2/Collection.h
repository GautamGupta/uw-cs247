#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include <vector>
#include "BCode.h"
#include "Building.h"

class Collection {
public:
    class BCodeNotFoundException : public BCode::BCodeException {
    public:
        BCodeNotFoundException(const std::string);
        virtual void printError() const;
    };

    class BCodeExistsException : public BCode::BCodeException {
    public:
        BCodeExistsException(const std::string);
        void printError() const;
    };

    class BCodeExistedException : public BCode::BCodeException {
    public:
        BCodeExistedException(const std::string);
        void printError() const;
    };

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
    Building* findWreckedBuilding(std::string);

    Node *_node;
    std::vector<Building*> wreckedBuildings;

};

#endif
