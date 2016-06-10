#include <fstream>
#include <iostream>
#include <string>
#include "BCode.h"
#include "Building.h"
#include "Collection.h"
#include "Graph.h"

using namespace std;

//************************************************************************
//  Test Harness Helper functions
//************************************************************************

namespace {

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

    void printNoChangeMessage() {
        cout << "This command results in no changes to the collection of buildings or to maps." << endl;
    }

    void printNoChangeMessage(int mapNum) {
        cout << "This command results in no changes to map" << mapNum << "." << endl;
    }

    void readBuilding(istream &source, Collection *buildings, Graph *map = NULL) {
        string code, name, name2;
        bool first = true;

        while (true) {
            source >> code;
            if (first) {
                source >> name;
                getline(source, name2);
                first = false;
            }
            if (!source) {
                break;
            }

            try {
                buildings->insert(code, name+name2);
                if (map != NULL) {
                    map->addNode(buildings->findBuilding(code));
                }
                break;
            } catch(BCode::InvalidFormatException &e) {
                e.printError();
                if (map != NULL) {
                    printNoChangeMessage();
                } else {
                    cout << "Please enter a new building code: ";
                }
            } catch(Collection::BCodeExistsException &e) {
                e.printError();
                if (map != NULL) {
                    printNoChangeMessage();
                } else {
                    cout << "Please enter a new building code: ";
                }
            } catch(Collection::BCodeExistedException &e) {
                e.printError();
                if (map != NULL) {
                    printNoChangeMessage();
                } else {
                    cout << "Please enter a new building code: ";
                }
            }
        }
    }

} // namespace

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
                    readBuilding(source, &buildings, &map1);
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
        int mapNum = (map == &map1) ? 1 : 2;

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
                readBuilding(cin, &buildings);
                break;
            }

                // add an existing building to the current map
            case node: {
                string code;
                cin >> code;

                try {
                    map->addNode( buildings.findBuilding( code ) );
                } catch(Graph::BCodeNotFoundException &e) {
                    cout << endl << "ERROR: There is no building with the code \"" << code << "\"." << endl;
                    printNoChangeMessage(mapNum);
                }

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

                try {
                    map->addEdge( code1, code2, type );
                } catch(Graph::BCodeNotFoundException &e) {
                    cout << endl << "ERROR: There is no building \"" << e.code() << "\" in map" << mapNum << " to use in the new edge." << endl;
                    printNoChangeMessage(mapNum);
                } catch(Graph::SelfConnectException &e) {
                    cout << endl << "ERROR: Cannot connect node \"" << e.code() << "\" to itself." << endl;
                    printNoChangeMessage(mapNum);
                } catch(Graph::InvalidConnectorTypeException &e) {
                    cout << endl << "ERROR:  There is no building connector of type \"" << e.type() << "\"." << endl;
                    printNoChangeMessage(mapNum);
                } catch(Graph::EdgeExistsException &e) {
                    cout << endl << "ERROR: There is already an edge between \"" << code1 << "\" and \"" << code2 << "\" in map" << mapNum << "." << endl;
                    printNoChangeMessage(mapNum);
                }

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

                try {
                    map->removeEdge( code1, code2 );
                } catch(Graph::BCodeNotFoundException &e) {
                    cout << endl << "ERROR: There is no building \"" << code1 << "\" in map" << mapNum << "." << endl;
                    printNoChangeMessage(mapNum);
                } catch(Graph::NoEdgeException &e) {
                    cout << endl << "ERROR: There is no edge in map" << mapNum << " between buildings \"" << code1 << "\" and \"" << code2 << "\" to be removed." << endl;
                    printNoChangeMessage(mapNum);
                }

                string junk;
                getline ( cin, junk );
                break;
            }

                // remove an existing node from the current map.  There is no change to the collection of Buildings.
            case remNode: {
                string code;
                cin >> code;

                try {
                    map->removeNode( code );
                } catch(Graph::BCodeNotFoundException &e) {
                    cout << endl << "ERROR: There is no building \"" << e.code() << "\" in map" << mapNum << " to be removed." << endl;
                    printNoChangeMessage(mapNum);
                }

                string junk;
                getline( cin, junk );
                break;
            }

                // remove an existing building from the collection of buildings.  The building also needs to be removed from the two maps, as well as all links involving the building
            case wreckage: {
                string code;
                cin >> code;

                try {
                    buildings.remove( code );
                    map1.removeNode( code );
                    map2.removeNode( code );
                } catch(Collection::BCodeNotFoundException &e) {
                    e.printError();
                    printNoChangeMessage();
                }

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

                try {
                    map->printPaths( code1, code2, printall );
                } catch(Graph::BCodeNotFoundException &e) {
                    cout << endl << "ERROR: There is no building \"" << e.code() << "\" in map" << mapNum << "." << endl;
                }

                string junk;
                getline( cin, junk );
                break;
            }

            default: {
                cerr << "Invalid command." << endl;
            }
        }

        cout << endl;
        cout << "Command: ";
        cin >> command;
        op = convertOp( command );

    } // while cin OK

}
