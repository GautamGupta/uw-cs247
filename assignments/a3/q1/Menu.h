#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>

#include "MenuComponent.h"
#include "ComponentIterator.h"

class Menu : public MenuComponent {
public:
    // iterator
    class iterator : public ComponentIterator {
    public:
        iterator( Menu* m = 0 );
    };

    // constructor
    Menu (const std::string);
    virtual ~Menu();

    // implement composite
    virtual void add( MenuComponent* newEntry );
    virtual void remove( std::string name );
    virtual int numChildren() const;
    virtual MenuComponent* getChild(int i) const;

    // implement shared operations
    virtual void menuDepthInc();
    virtual int size() const;
    virtual ComponentIterator begin();
    virtual ComponentIterator end();

protected:
    virtual void print ( std::ostream& ) const;

private:
    std::vector<MenuComponent*> entries_;
};

#endif
