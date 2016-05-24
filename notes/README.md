*Lecture 1 - May 3 2016*

# Admin

 - ssh: linux.student.cs.uwaterloo.ca, ~cs247 folder
 - cs246 a0 for git instructions

# Overview

**Q. How would you describe software engineering?**

Collection of tools, principles, techniques, processes, etc to improve:

 - Software quality + design
 - Productivity
 - Scalability
 - Evolvability

**Q. Why "object oriented" design?**

 - Shared vocabulary
 - Closer to client domain
 - Raise the level of abstraction
 - Re-use
 - Modularity (decompose problem into classes)
 - Information hiding, encapsulate design decisions
 - Polymorphism

**Terminology**

 - virtual, pure virtual
 - base, super class, sub class
 - abstract base class

*Lecture 2 - May 5 2016*

# Abstract Data Types (ADTs)

We would like our client code to only know our ADT, through its interface

 - Range of data, but not its representation
 - Operations, but not their implementation

 - For safety: Restrict values to desired range => operations leave data in valid state. Therefore want "tool-supported" safety, checked via compiler.
 - Evolvability: Since client code only depends on interface, implementation can change without impacting client
 - Productivity: Checks data, ranges for us but only where required => constructors, mutability operators

ADT Implementation -> ADT Interface -> Use case / scenario development (test harness + cases)

Use ADTs aggressively whenever need to restrict data ranges, customize data, customize operations.
Goal: Consistent, complete & encapsulated

### Example: Rational Numbers

 - Default construction. Valid value == 0 for numerator, 1 for denominator
 - Destructor: Default is probably ok
 - Other constructor (allow both, default denominator to 1, also default numerator to 0 gets rid rid of default constructor)
 - Compiler copy consturctor is fine
 - Assignment
 - Arithmetic (overload +, -, *, /)
 - I/O (>>, <<)
 - Equality: Should reduce first? What about other operations?
 - Return value optimization: Return anonymous objects where possible (`return RationalNumber(n, d)`)
 
*Lecture 3 - May 10*

## Attribute-based ADT

 - Class interface based entirely on attributes (data members)
 - Public interface is simply accessors or mutators
 - All other functions are non-members
 - Use override keyword as appropriate, self-documentation
 
### Example: Entity or Value based ADT

Consider a computer card game such as "straights" (your project).

Object | Entity | Value | Comments
------ | ------ | ----- | --------
Card   | Y      |       | const
Deck   | Y      | 
Hand   | Y      | 
Player | Y      | 
Score  |        | Y

## Singleton Design Patterns

### Alternative

 - Use pointer (static); if never used, no allocation.
 - Public accessor responsible for creation
 - Destructor responsible for deletion
 
## Example: StudentADT

 - Entity
 - Student ID # <- Value ADT to enforce range checking
 - Name (length constraints? preferred name? UTF encoding?)
 - Gender
 - Grades (0-100 and cutoff at 32, "F-A", AEG, DNW, INC, UR, ...)
 - License (length 8 including space -- 3 uppercase letters, space, 3 digits, default constructor generates "next" from static data member, vanity plates restrict values)
 
## Rational.cc

 - If mark rational as final, count inherit
 - Could mark methods as final -> no override
 
*Lecture 4 - May 12*
 
## Rule of 3 aka Big 3

 - Copy constructor
 - Destructor
 - Assignment operator
 
 - If define 1 (or more), define all 3
 - C++11 expands it to "Rule of 5" by adding concept of "rvalues" modifiable temporaries. `MyClass v{}`
 
 - Identified by T&& set up by `std::move()`
 - ie. add move constructor and move assignment to the list
 - these, plus default destructor, provided by compiler unless overriden by user
 
Example

```
class Base;
class C;

class MyClass::public Base {
	private:
		C comp_;
		C *ptr_;
		int simple_;
	public:
		MyClass();
		~MyClass();
		MyClass(const MyClass&);
		MyClass(const MyClass&&);
		MyClass & operator=(const MyClass&));
		MyClass & operator=(const MyClass&&);
		
		friend bad operator== (const MyClass&, const MyClass&);
}
```

## "Self-assignment"

```
MyClass a;
a = a
```

 - `operator=` check that not assigning to same object ie. "other" != "this"
 - it get past test, invoke copy & swap
 
## Move/Copy

How does a compiler know to move or copy? Language rules, eg. for return values, may suggest a move ()return value optimization). Otherwise, programmer specifies by supplying an rvalue throudh std::move, which returns an rvalue but *doesn't* do the move.

## Appendix

 - Mutable: Can change
 - Immutable: Can't change
 
*Lecture 5 - May 17*

##Value vs Entity ADT

 - Extra info
 

## Globals

 - Try to resitrict yourself to only global constants, and not variables
 - Use `extern` to mark it => not a space allocation => must remember to allocate space, but only once.
 - **Guards**: Use preprocessor macros & the compilter to ensure only ever 1 definition

```
#ifdef
#endif
#ifndef RATIONAL_H
#define RATIONAL_H
#include <> // start with libraries, then local
#include " " // keep relative
```




.

.

.

.

.

.
