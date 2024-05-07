#include <iostream>
#include <memory>

using namespace std;

// Subquestion (a) - Fixing the code
struct Base
{
    virtual void draw() { std::cout << "print a base\n"; }
    void print() {}

    //~Base() { std::cout << "bye base\n"; }
    // we know the rule that if any member function of a class is virtual; 
    // then its destructor must be virtual as well
    // if not, it can lead to undefined behaviour if an object of type Derived
    // is deleted through a Base pointer
    // corrected version:
    virtual ~Base() { std::cout << "bye base\n"; }
};

struct Derived final : public Base
{
    Derived() {}
    void draw() override { std::cout << "print a derived\n"; }

    // void draw() const override {} 
    // above line does not compile because:
    // this does not override a base class member; const-ness is a part of function signature;
    // on removing the 'override' keyword, this function becomes an independent member function of Derived
    // corrected version:
    void draw() const{
        cout << "print a non-override derive\n";
    }

    // void print() override {}
    // above line does not compile because:
    // trying to override a non-virtual function of the base class
    // corrected version
    void print() {
        cout << "from the print() of Derived struct\n";
    }
    ~Derived() { std::cout << "bye derived\n"; }
};

int main()
{
    // testing the code using smart pointers
    // using the std::unique_prt
    // Subquestion (b)
    unique_ptr<Base> base_ptr = std::make_unique<Base>();
    unique_ptr<Derived> derived_ptr = std::make_unique<Derived>();
    unique_ptr<Base> derived_ptr2 = std::make_unique<Derived>();


    base_ptr->draw();

    derived_ptr->draw();
    derived_ptr->print();



    cout << "\n\ngoing out of scope; objects being destroyed...\n";

    /* 
    * after making changes to the destructor of the Base; correct object destruction takes place:
    * 
    * 
        going out of scope; objects being destroyed...
        bye derived         ###
        bye base
        bye derived
        bye base
        bye base
    * 
    * without that correction, this is the destruction sequence:
        bye base
        bye derived
        bye base
        bye base
    * derived object not destryoed for derived_ptr2
    */

    return 0;
}