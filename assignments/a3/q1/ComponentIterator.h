#ifndef MC_ITERATOR_H
#define MC_ITERATOR_H

#include <stack>
#include <iterator>

class MenuComponent;

class ComponentIterator : std::iterator< std::forward_iterator_tag, MenuComponent* > {
    friend bool operator== ( const ComponentIterator&, const ComponentIterator& );
    friend bool operator!= ( const ComponentIterator&, const ComponentIterator& );
    friend void operator++( ComponentIterator& );
    friend void operator++( ComponentIterator&, int );
public:
    ComponentIterator( MenuComponent* = 0 );
    ~ComponentIterator();
    // ComponentIterator( const ComponentIterator& );
    bool hasNext();
    MenuComponent* operator->() const;
    MenuComponent* operator* () const;
private:
    // MenuComponent* menu_;
    struct IterNode {
        MenuComponent *node_;
        int cursor_;
        IterNode(MenuComponent*, int cursor_);
    };
    std::stack<IterNode*> istack_;
};

bool operator== ( const ComponentIterator&, const ComponentIterator& );
bool operator!= ( const ComponentIterator&, const ComponentIterator& );
void operator++( ComponentIterator& );
void operator++( ComponentIterator&, int );

#endif
