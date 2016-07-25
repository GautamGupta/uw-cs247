#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>

#include "MenuComponent.h"
#include "ComponentIterator.h"

class Menu : public MenuComponent {
public:
    class Iterator : public ComponentIterator {
    public:
        Iterator( Menu* = 0 );
    };

    // constructor
    Menu (const std::string);
    virtual ~Menu();

    // implement composite
    virtual void add( MenuComponent* );
    virtual void remove( std::string );
    virtual int numChildren() const;
    virtual MenuComponent* getChild(int) const;

    // implement shared operations
    virtual void menuDepthInc();
    virtual int size() const;

protected:
    virtual void print ( std::ostream& ) const;

private:
    std::vector<MenuComponent*> entries_;
};

#endif
