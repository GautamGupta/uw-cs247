#include <string>
#include <iostream>

#include "MenuItem.h"
#include "Menu.h"

using namespace std;


//************************************************************************
//  Helper variables and functions for test harness
//************************************************************************

// Exception classes for test harness
class SyntaxError {};
class BadIndex {};
class MenuNotFound {
    public:
        MenuNotFound ( string name ) : name_(name) {}
        string name() const { return name_; }
    private:
        string name_;
};
class NoMenu {
    public:
        NoMenu ( int index ) : index_(index) {}
        int index() const { return index_; }
    private:
        int index_;
};

//  test harness commands
enum Op {NONE, MENU, ITEM, AddC, Remove, Print, DONE};


// parse input command
Op convertOp(string opStr) {
    switch (opStr[0]) {
        case 'm': return MENU;
        case 'a': return AddC;
        case 'i': return ITEM;
        case 'r': return Remove;
        case 'p': return Print;
        case 'd': return DONE;
        default: return NONE;
    }
}


// try to clean up the stream after sin.fail()
void sinCleanup ( istream& sin ) {
    cin.clear();
    string junk;
    getline( sin, junk );
}


// parse name of menu that is to be operated on
int readIndex( istream& sin ) {
    int index = -1;
    sin >> index;
    if ( index >= 0 && index <= 9 ) return index;

    // try to fix sin
    sinCleanup( sin );

    throw BadIndex();
}

string readName( istream& sin ) {
    char quotes;
    string name;

    sin >> quotes;
    getline( sin, name, '\"');

    if ( sin.fail() ) {
        sinCleanup( sin );
        throw SyntaxError();
    }

    return name;
}



//*******************
// main()
//*******************

int main ( ) {
    cout << "Test harness for Menu Composite and Iterator" << endl << endl;

    // create a collection of menus to manipulate
    MenuComponent* menus[10] = {0};

    // enable reading of boolean values "true" and "false"
    cin >> boolalpha;

    // get input command
    cout << "Command: ";
    string command;
    cin >> command;

    Op op = convertOp(command);

    //**********************************
    // Populate the Composite Menu
    //**********************************
    while ( !(op==DONE) ) {
        try {
            switch (op) {
                case MENU: {
                    int index = readIndex( cin );
                    string name = readName( cin );
                    delete menus[index];
                    menus[index] = new Menu( name );
                    break;
                }

                case AddC: {
                    int index = readIndex( cin );
                    int index2 = readIndex( cin );
                    if ( !menus[index] ) throw NoMenu( index );
                    if ( !menus[index2] ) throw NoMenu( index2 );
                    menus[index]->add(menus[index2]);
                    menus[index2] = NULL;
                    break;
                }

                case ITEM: {
                    int index = readIndex( cin );
                    string name = readName( cin );

                    float price;
                    int calories;
                    bool veg;
                    cin >> price >> calories >> veg;
                    if ( cin.fail() ) {
                        sinCleanup( cin );
                        throw SyntaxError();
                    }

                    delete menus[index];
                    menus[index] = new MenuItem ( name, price, calories, veg );
                    break;
                }

                case Print: {
                    int index = readIndex( cin );
                    if ( !menus[index] ) throw NoMenu( index );

                    for ( auto it = menus[index]->begin(); it != menus[index]->end(); it++ ) {
                        cout << *it << endl;
                    }

                    break;
                }

                case Remove: {
                    int index = readIndex( cin );
                    if ( !menus[index] ) throw NoMenu( index );

                    string name = readName( cin );
                    menus[index]->remove( name );
                    break;
                }

                default: {
                    cout << "Invalid command." << endl;
                    break;
                }
            } // switch command
        } // try

        catch ( NoMenu& e ) {
            cout << "Menu Element " << e.index() << " does not exist." << endl;
        }
        catch ( BadIndex& ) {
            cout << "Invalid name of menu!" << endl;
        }
        catch ( SyntaxError& ) {
            cout << "Command has syntax errors. No change to menu." << endl;
        }
        catch ( MenuComponent::InvalidOp& ) {
            cout << "Command is invalid on Menu Items. No change to menus." << endl;
        }

        cout << endl << "Command: ";
        cin >> command;
        op = convertOp(command);


    } // while cin OK

    cout << endl << "Veggie Items:" << endl;
    for_each(menus[0]->begin(), menus[0]->end(), [](const MenuComponent &item) {
        if (item.isVeggie()) {
            cout << "\t" << item.name() << ", $" << item.price() << ", cal=" << item.calories() << " (V)" << endl;
        }
    });

    for ( int i = 0; i < 10; i++ ) {
        if ( menus[i] )
            delete menus[i];
    }
}
