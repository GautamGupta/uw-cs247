
#include <sstream>
#include <iomanip>

#include "MenuItem.h"


using namespace std;

// **********************************************************************
// MenuItem
// **********************************************************************

MenuItem::MenuItem( const string name, float price, int cal, bool veggie) :
    MenuComponent(name), price_(price), calories_(cal), isVeggie_(veggie) {}


bool MenuItem::isVeggie() const {
    return isVeggie_;
}

float MenuItem::price() const {
    return price_;
}

void MenuItem::priceIs( float p ) {
    price_ = p;
}

int MenuItem::calories() const {
    return calories_;
}

void MenuItem::caloriesIs ( int c ) {
    calories_ = c;
}

void MenuItem::print ( ostream& sout ) const {
    sout.precision(2);
    sout.setf(ios::fixed, ios::floatfield);
    sout << menuDepth() << name() << ", $" << price() << ", cal=" << calories();
    if ( isVeggie() )
        sout << " (V)";
}
