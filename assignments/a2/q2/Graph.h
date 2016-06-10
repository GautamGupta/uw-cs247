#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "Building.h"
#include "Collection.h"

class Graph {
public:
    class BCodeNotFoundException {
    public:
        BCodeNotFoundException();
    };

    Graph();                                                             // constructor
    ~Graph();                                                            // destructor
    Graph(const Graph&);                                                 // copy constructor
    void addNode(Building*);                                            // mutator - add node to graph
    void removeNode(std::string);                                        // mutator - remove node from graph
    Building* findBuilding(std::string) const;                           // accessor - find building stored in node in graph
    void addEdge(std::string, std::string, std::string);                 // mutator - add edge to graph
    void removeEdge(std::string, std::string);                           // mutator - remove edge from graph
    void printPaths(std::string, std::string, const bool = false) const; // accessor - print path from one node to another
    void deleteGraph();                                                  // delete graph
    friend std::ostream& operator<<(std::ostream&, const Graph&);        // insertion operator (insert graph into output stream)
    Graph& operator=(const Graph&);                                      // assignment operator for graph objects
    bool operator==(const Graph&) const;                                 // equality operator for graph objects

private:

    struct Node; // used by Connector

    struct Connector {
        Node *node;
        Connector *next;
        std::string type;

        Connector(Node *node, Connector *next, std::string type) :
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
    Node* findNode(std::string) const;
    Node* deleteNode(Node*);
    void addConnector(Node*, Node*, std::string);
    void deleteConnector(Node*, BCode);
    bool static isNodeEqual(Node*, Node*);

    Node* nodes() const;
    Node *_node;

};

#endif
