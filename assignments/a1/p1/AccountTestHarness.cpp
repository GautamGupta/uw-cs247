#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <stdio.h>


using namespace std;


//***********************
// Account Number ADT
//***********************

class AccountNo {                       /* Value range: 0001-9999 */
public:
    AccountNo ();                       /* New account number                          */
    explicit AccountNo ( int number );  /* Existing account number (for lookups)       */
    int number () const;                /* Accessor -- integer value of account number */
private:
    int number_;
    static int next_;
    static int const maxVal_ = 9999;
};


// initialization of static data member to the lowest legal value
int AccountNo::next_ = 1;


// constructor -- constructs a new unique account number
AccountNo::AccountNo () {
	if ( next_ > maxVal_ )
        exit (1);
    number_ = next_++;
}

// constructor -- converts an integer into an account number
// REQUIRES:  number corresponds to an existing account number
AccountNo::AccountNo ( int number ) {
	if ( (number > maxVal_) || (number < 1) )
		exit(1);
	number_ = number;
}


// accessor - returns account number value of object
int AccountNo::number() const {
	return number_;
}


// comparison operators
bool operator== (const AccountNo &a, const AccountNo &b) {
	return a.number() == b.number();
}

bool operator!= (const AccountNo &a, const AccountNo &b) {
	return !(a==b);
}

bool operator< (const AccountNo &a, const AccountNo &b) {
	return a.number() < b.number();
}

bool operator<= (const AccountNo &a, const AccountNo &b) {
	return (a<b) || (a==b);
}

bool operator> (const AccountNo &a, const AccountNo &b) {
	return !(a<=b);
}

bool operator>= (const AccountNo &a, const AccountNo &b) {
	return !(a<b);
}


// streaming operators
istream& operator>> ( istream &sin, AccountNo &a ) {
	int number;
	sin >> number;
	a = AccountNo(number);

	return sin;
}

ostream& operator<< ( ostream &sout, const AccountNo &a ) {
	sout.setf(ios::internal);
	sout.width(4);
	sout.fill('0');
	sout << a.number();

	return sout;
}


//*******************
// Account
//*******************

class Account {
public:                                             // PUBLIC interface of Account
	explicit Account(const AccountNo&);             // constructor
	virtual ~Account() {}                           // destructor
	int balance() const;                            // accessor - returns balance as an integer
	virtual void call(int) = 0;                     // records information about a call (e.g., duration of call in minutes)
	virtual void bill() = 0;                        // decrements balance by monthly fee and the cost of using extra minutes
	void pay(int);                                  // increments balance by amount paid
	virtual void print() const;                     // prints information about the account (e.g., account number, balance, minutes used this month

protected:
    void set_balance(const int);
    static void _print(string, string);

private:
    int _balance;
    AccountNo _account_no;
};

//************************************************************************
//* YOUR IMPLENTATION OF ACCOUNT, CHEAP_ACCOUNT, EXPENSIVE_ACCOUNT HERE
//************************************************************************

/**
 * Account with 0 balance
 */
Account::Account(const AccountNo& acc_no) :
        _account_no(acc_no),
        _balance(0) {}

/**
 * @return int Balance
 */
int Account::balance() const {
    return _balance;
}

/**
 * Pay the bill (increases balance)
 */
void Account::pay(int amount) {
    set_balance(balance() + amount);
}

/**
 * Prints account information
 */
void Account::print() const {
    string bal = balance() < 0 ? "-" : "";
    bal += "$" + to_string(abs(balance()));

    char acc_no[4];
    sprintf(acc_no, "%04d", _account_no.number());

    _print("Account Number", acc_no);
    _print("Balance", bal);
}

/**
 * Set balance to specified amount
 */
void Account::set_balance(const int balance) {
    _balance = balance;
}

/**
 * Print Statement Helper Function
 */
void Account::_print(string desc, string value) {
    cout << "  " << desc << " = " << value << endl;
}

class CheapAccount : public Account {
public:                                             // PUBLIC interface of CheapAccount
    explicit CheapAccount(const AccountNo&);        // constructor
    ~CheapAccount() {}                              // destructor
    void call(int);                                 // records information about a call (e.g., duration of call in minutes)
    void bill();                                    // decrements balance by monthly fee and the cost of using extra minutes
    void print() const;                             // prints information about the account (e.g., account number, balance, minutes used this month

private:
    int _minutes;                                   // Minutes of calls that have been made
    static int const CAD_MONTHLY  = 25;             // $25 monthly bill
    static int const CAD_MINUTE   = 1;              // $1 per minute charge over MINUTES_FREE
    static int const MINUTES_FREE = 250;            // Amount of free minutes per month
};

CheapAccount::CheapAccount(const AccountNo& acc_no) :
        Account(acc_no),
        _minutes(0) {}

void CheapAccount::call(int duration) {
    _minutes += duration;
}

void CheapAccount::bill() {
    set_balance(balance() - CAD_MONTHLY);

    if (_minutes > MINUTES_FREE) {
        set_balance(balance() - ((_minutes - MINUTES_FREE) * CAD_MINUTE));
    }

    _minutes = 0;
}

void CheapAccount::print() const {
    cout << "CheapAccount:" << endl;
    Account::print();
    Account::_print("Minutes", to_string(_minutes));
}

class ExpensiveAccount : public Account {
public:                                             // PUBLIC interface of CheapAccount
    explicit ExpensiveAccount(const AccountNo&);    // constructor
    ~ExpensiveAccount() {}                          // destructor
    void call(int);                                 // records information about a call (e.g., duration of call in minutes)
    void bill();                                    // decrements balance by monthly fee and the cost of using extra minutes
    void print() const;                             // prints information about the account (e.g., account number, balance, minutes used this month

private:
    static int const CAD_MONTHLY = 80;              // $25 monthly bill
};

ExpensiveAccount::ExpensiveAccount(const AccountNo& acc_no) :
        Account(acc_no) {}

void ExpensiveAccount::call(int duration) {}

void ExpensiveAccount::bill() {
    set_balance(balance() - CAD_MONTHLY);
}

void ExpensiveAccount::print() const {
    cout << "ExpensiveAccount:" << endl;
    Account::print();
}

//************************************************************************
//  Helper variables and functions for test harness
//************************************************************************

//  test-harness operators
enum Op { NONE, NewE, NewC, Balance, Call, Bill, Pay, PrintAll };


//  converts a one-character input comment into its corresponding test-harness operator
Op convertOp( string opStr ) {
    switch( opStr[0] ) {
        case 'E': return NewE;
        case 'C': return NewC;
        case 'b': return Balance;
        case 'c': return Call;
        case 'B': return Bill;
        case 'p': return Pay;
        case 'P': return PrintAll;
        default: {
            cerr << "Invalid operation " << opStr << endl;
            return NONE;
        }
    }
}


// Reads a number from cin and finds the corresponding Account
// REQUIRES: the next word to read from cin is an integer
// RETURNS: a pointer to a found account.  Otherwise, returns NULL
Account* findAccount( map<AccountNo,Account*>  &accounts) {
    int num;
    cin >> num;
    AccountNo act( num );
    map<AccountNo,Account*>::iterator iter;
    iter = accounts.find( act );
    if ( iter == accounts.end() ) {
        cerr << "Invalid Account Number!" << endl;
        return NULL;
    }
    return iter->second;
}


//*******************
// main()
//*******************

int main () {
    cout << "Test harness for family of phone-service accounts:" << endl << endl;
    map<AccountNo, Account*> accounts;

    cout << "Command: ";
    string command;
    cin >> command;

    Op op = convertOp(command);

    while ( !cin.eof() ) {
        switch ( op ) {
            /* Constructors */

            case NewE: {
                AccountNo act;
                Account* p = new ExpensiveAccount( act );
                accounts.insert( pair<AccountNo,Account*>( act, p ) );
                p->print();
                break;
            }
            case NewC: {
                AccountNo act;
                Account* p = new CheapAccount( act );
                accounts.insert( pair<AccountNo,Account*>( act, p ) );
                p->print();
                break;
            }

            /* Accessors */

            case Balance: {
                Account* p = findAccount( accounts );
                if ( p!= NULL)
                    cout << "Value of balance data member is: " << p->balance() << endl;
                break;
            }

            /* Phone Service Operations */

            case Call: {
                Account* p = findAccount( accounts );
                if ( p != NULL ) {
                    int duration;
                    cin >> duration;
                    p->call( duration );
                }
                break;
            }


            case Bill: {
                map<AccountNo,Account*>::iterator iter;
                map<AccountNo,Account*>::iterator end = accounts.end();
                for ( iter = accounts.begin(); iter != end; iter++ ) {
                    (iter->second)->bill();
                }
                break;
            }


            case Pay: {
                Account* p = findAccount( accounts );
                if (p != NULL ) {
                    int amt;
                    cin >> amt;
                    p->pay(amt);
                }
                break;
            }


            /* Print Accounts */

            case PrintAll: {
                map<AccountNo,Account*>::iterator iter;
                map<AccountNo,Account*>::iterator end = accounts.end();
                for ( iter = accounts.begin(); iter != end; iter++ ) {
                    (iter->second)->print();
                }
                break;
            }
            default: {
                break;
            }
        } // switch

        cout << endl << "Command: ";
        cin >> command;
        op = convertOp(command);

    } // while cin OK

    map<AccountNo,Account*>::iterator iter;
    map<AccountNo,Account*>::iterator end = accounts.end();
    for ( iter = accounts.begin(); iter != end; iter++ )
      delete iter->second;

    return 0;
}
