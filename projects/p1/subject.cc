/**
 * Subject class.  Abstract class for Observer Pattern
 */

#include <set>
#include "subject.h"
#include "observer.h"

void Subject::subscribe(Observer *newView) {
    observers_.insert(newView);
}

void Subject::unsubscribe(Observer *formerView) {
    observers_.erase(formerView);
}

void Subject::notify() {
    for (Observers::iterator i = observers_.begin(); i != observers_.end(); ++i) {
        (*i)->update();
    }
}
