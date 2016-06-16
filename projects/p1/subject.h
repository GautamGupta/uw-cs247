/**
 * Subject class.  Abstract class for Observer Pattern
 */

#ifndef ST_SUBJECT_H
#define ST_SUBJECT_H

#include <set>

class Observer;

class Subject {
public:
       void subscribe(Observer*);
       void unsubscribe(Observer*);

protected:
       void notify();

private:
       typedef std::set<Observer*> Observers;
       Observers observers_;
}; // Subject


#endif
