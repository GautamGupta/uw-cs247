#include <stack>
#include <iterator>
#include "ComponentIterator.h"
#include "MenuComponent.h"

using namespace std;

ComponentIterator::ComponentIterator( MenuComponent *menuComponent /* = 0 */ ) : menu_(menuComponent) {}

ComponentIterator::~ComponentIterator() {}

ComponentIterator::ComponentIterator( const ComponentIterator& ) {

}

MenuComponent* ComponentIterator::operator->() const {
    return NULL;
}

MenuComponent* ComponentIterator::operator* () const {
    return NULL;
}

void ComponentIterator::begin() {

}

bool operator== ( const ComponentIterator&, const ComponentIterator& ) {
    return false;
}

bool operator!= ( const ComponentIterator&, const ComponentIterator& ) {
    return false;
}

void operator++( ComponentIterator& ) {

}

void operator++( ComponentIterator&, int ) {

}
