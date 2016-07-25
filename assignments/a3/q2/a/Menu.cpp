#include <iostream>
#include <vector>
#include <string>

#include "Menu.h"

using namespace std;

//****************************************************************************
// MENU
//****************************************************************************

Menu::Menu (const string name) : MenuComponent(name) {}

Menu::~Menu() {
	for (auto it = entries_.begin(); it != entries_.end(); ++it) {
        if (*it) {
            delete *it;
            *it = NULL;
        }
    }
}


void Menu::add( MenuComponent* newEntry ) {
    newEntry->menuDepthInc();
    entries_.push_back( newEntry );
}


void Menu::remove( string name ) {
    for ( auto it = entries_.begin(); it != entries_.end(); it++ ) {
        if ( (*it)->name() == name ) {
            delete *it;
            entries_.erase( it );
            return;
        }
    }
}


int Menu::numChildren() const {
    return entries_.size();
}


int Menu::size() const {
    int size = 1;

    for ( auto it = entries_.begin(); it != entries_.end(); it++ ) {
        size += (*it)->size();
    }

    return size;
}


MenuComponent* Menu::getChild( int i ) const {
    return entries_.at(i);
}


void Menu::menuDepthInc() {
    vector<MenuComponent*>::iterator it;

    MenuComponent::menuDepthInc();
    for (it = entries_.begin(); it != entries_.end(); it++ ) {
        (*it)->menuDepthInc();
    }
}

void Menu::print ( ostream& sout ) const {
    sout << "\n" << menuDepth() << name() << ":";
}

Menu::Iterator::Iterator(Menu *menu) : ComponentIterator::ComponentIterator(menu) {}
