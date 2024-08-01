//
// A virtual constructor is not possible but virtual destructor is possible.
// The construction of derived object follow the construction rule but when we delete the "b" pointer(base pointer) we have found that only the base destructor is called. 
// But this must not happen. To do the appropriate thing, we have to make the base destructor virtual.
//
// Output when ENABLE_VIRTUAL_DESTRUCTOR is not defined
//
// Base Constructor Called
// Derived Constructor Called
// Base Destructor Called
//
// Output when ENABLE_VIRTUAL_DESTRUCTOR
//
// Base Constructor Called
// Derived Constructor Called
// Derived Destructor Called
// Base Destructor Called
//
// So the destruction of the base pointer (which takes an allocation on derived object!) follows the destruction rule, i.e first the Derived, then the Base.
//
#include <iostream>

using namespace std;

#define VIRTUAL_DESTRUCTOR true

class Base
{
public:
    Base() {
        cout << "Base Constructor Called\n";
    }
#if VIRTUAL_DESTRUCTOR
    virtual ~Base() {
#else
    ~Base() {
#endif
        cout << "Base Destructor Called\n";
    }
};

class Derived1 : public Base
{
public:
    Derived1() {
        cout << "Derived Constructor Called\n";
    }
    ~Derived1() {
        cout << "Derived Destructor Called\n";
    }
};

int main()
{
    Base* b = new Derived1();
    delete b;
}
