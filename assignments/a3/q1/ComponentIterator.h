#ifndef MC_ITERATOR_H
#define MC_ITERATOR_H

#include <stack>
#include <iterator>
#include "MenuComponent.h"

class ComponentIterator : std::iterator< std::forward_iterator_tag, MenuComponent* > {
    friend bool operator== ( const ComponentIterator&, const ComponentIterator& );
    friend bool operator!= ( const ComponentIterator&, const ComponentIterator& );
    friend void operator++( ComponentIterator& );
    friend void operator++( ComponentIterator&, int );
public:
    ComponentIterator( MenuComponent* = 0 );
    ~ComponentIterator();
    ComponentIterator( const ComponentIterator& );
    MenuComponent* operator->() const;
    MenuComponent* operator* () const;
    void begin();
private:
    MenuComponent* menu_;
    std::stack<MenuComponent*> istack_;
};

bool operator== ( const ComponentIterator&, const ComponentIterator& );
bool operator!= ( const ComponentIterator&, const ComponentIterator& );
void operator++( ComponentIterator& );
void operator++( ComponentIterator&, int );

#endif
