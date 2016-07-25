#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <iostream>
#include <string>

#include "ComponentIterator.h"
#include "MenuComponent.h"

class MenuItem : public MenuComponent {
public:
    class Iterator : public ComponentIterator {
    public:
        Iterator( MenuItem* = 0 );
    };

    // constructor
    MenuItem(const std::string, float, int, bool);
    virtual ~MenuItem() {}

    // implement leaf operations
    virtual bool isVeggie() const;
    virtual float price() const;
    virtual void priceIs( float );
    virtual int calories() const;
    virtual void caloriesIs( int );

    // implement shared operations

protected:
    virtual void print ( std::ostream& ) const;

private:
    float price_;
    int calories_;
    bool isVeggie_;
};

#endif
