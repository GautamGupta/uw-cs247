#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <iostream>
#include <string>

#include "ComponentIterator.h"
#include "MenuComponent.h"

class MenuItem : public MenuComponent {
public:
    class iterator;
    friend class iterator;
    class iterator : public ComponentIterator {
    public:
        iterator( MenuItem* mi = 0 );
    };

    // constructor
    MenuItem(const std::string, float, int, bool);
    virtual ~MenuItem() {}

    // implement leaf operations
    virtual bool isVeggie() const;
    virtual float price() const;
    virtual void priceIs( float p );
    virtual int calories() const;
    virtual void caloriesIs( int c );

    // implement shared operations
    virtual ComponentIterator begin();
    virtual ComponentIterator end();

protected:
    virtual void print ( std::ostream& ) const;

private:
    float price_;
    int calories_;
    bool isVeggie_;
};

#endif
