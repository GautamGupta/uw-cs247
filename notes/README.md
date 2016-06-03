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

*Lec 7 - May 24*

## "modifies" vs "const"

 - modifies: lists all data changed, including global variables
 - const: immutability checked by compiler. ensures `this->minutes == this->balance@pre + fee + (minutes->freeminutes ? minutes->freeminutes * rate : 0)`

## Comparing Specifications

NB:one isn't necessarily better than the other ie. each has a place.

Strong => tolerant on input, demanding on output

Weak => demanding on inputs, tolerant on outputs

a module with strong specifications can always substitute for a module with weak specs


### "Confirming Specifications" slide

5 >= 2 == 4 >= 3 => 1

# Exception Handling

## Return values / global error flags

### Disadvantages

 - Passive / no enforcement of checking 
 - Error value might have changed before check (multi-threaded environment)
 - Checks proliferate through code + have to be maintained => inefficient
 - Could mix in valid + error values => have to parse
 - Doesn't work for all situations eg. constructor fails
 - Testing has to be local, but may not be right "level"
 - Non-local error handling may need to pass up more than one error value => proliferation of errors

## Exceptions

Let's separate error handling code from "regular" code
 - Termination exception handling mode:
 
```
most specific (catch blocks)
 | try {
 | 	...
 | } catch (...) {}
\/
least
```

Re-raise

```
throw; // inside a catch statement
```

*Lec 8 - May 25*

## Stack unwinding

See `exception.cpp`

Can embed try/catch in initializer

```
MyClass::MyClass(C c, C* p2) 
	try: c_©, p_(new c), p2_(p2) {}
	catch (...) {
		delete p_;
		throw MyClass::Error();
	}
	
```

C++ standard library provides:

 - At least basic guarantee for all operations
 - Strong guarantee on a few key operations eg. push_back, single element insert on a list, uninitialized copy()
 - No throw on swap() of 2 containers + pop_back()
 
`unique_ptr<Rational> ar(new Rational());`
 
Works only if you don't leave things in an invalid state, don't leak resources and destructors can't throw exceptions.

Resources could be memory, file locks, network connections, etc.

"Source and Sink Idiom" useful only if creation/consumption

 - `unique_ptr` not the same thing as "regular" C++ pointer so can't assign one to other
 - Can't assign multiple `unique_ptr`s to same object
 - Can't pass as reference for either parameter or return value; passing by value transfers ownership
 - `auto_ptr` is deprecated; do not use -- use other `unique_ptr` or `shared_ptr`/`weak_ptr` instead
 
 - Use assertions to check for logic errors
 - Use exceptions to report "environmental" errors esp if client input is in error since can be handled; whereas assertion violation would terminate program
 - Since assertion violation terminates program right away, helpful since cause is "logically near". Therefore easier to debug.
 
throwexceptions:
 - in constructor if can't create valid object
 - in mutators if they try to set state to be invalid => ensure object is in previous, valid state

Never throw exceptions:
 - in destructors (hard to catch + deal with)
 - Copy constructor / assignment operator
 - Accessors
 - Value operators eg. operation ==, <, &&
 - Try to avoid mutating operators eg. operation +, etc
 
# Abstraction Function

 - No duplicate values forall `0 <= i`, `j < size` |
 	`i != j => elements[i] != elements[j]`
 - Above size, pointers are null forall `i > size-1` | `elements[i] == nullptr`
      => in remove, set `elements[size-1] == nullptr` before decrement size
  => initialize array in constructor
 - default constructor causes memory leak, but doesn't violate rep inv.
 
List with dummy header node whose `(Data*) == nullptr`; all other nodes have `(Data*) != nullptr` & circualr, doubly-linked list

# Representation Invariant

 - Must have a header node (ie. not null)
 - Data field of header node is null
 - Node object pointed to by only one next and one previous field
 - For any 2 objects `n1 + n2` if `n1.next == n2` then `n2.prev == n1`
 - Header node has null data field
 - List entries do not have null data fields 
 
 `Node(Data*, Node *p, Node *n)`
 

.

.

.

.

.

.
