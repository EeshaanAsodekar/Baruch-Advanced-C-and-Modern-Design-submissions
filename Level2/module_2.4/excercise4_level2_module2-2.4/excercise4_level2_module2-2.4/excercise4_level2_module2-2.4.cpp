#include <iostream>
#include <list>

// Base class
class Base
{
private:
public:
    Base() { }
    virtual void print() const = 0;
    virtual ~Base() { std::cout << "Base destructor\n\n"; }// destructor needed to be shifted here
//protected:
    //virtual ~Base() { std::cout << "Base destructor\n\n"; }// gives compile time error
    // C2248: 'Base::~Base': cannot access protected member declared in class 'Base'
};

// Derived class
class Derived : public Base
{
private:
public:
    Derived() : Base() { std::cout << "Derived Constructor\n"; }
    ~Derived() { std::cout << "Derived destructor\n"; }
    void print() const { std::cout << "derived object printing\n"; }
};

// Factory function
// Subquestion (b)
std::shared_ptr<Base> createBase()
{
    std::shared_ptr<Base> result(new Derived());
    return result;
}

int main()
{
    // stl list of shared_ptr to base
    using shared_ptr_list = std::list<std::shared_ptr<Base>>;
    using unique_ptr_list = std::list<std::unique_ptr<Base>>;

    shared_ptr_list shared_derived_ptr_list;
    unique_ptr_list unique_derived_ptr_list;

    // Subquestion (a)
    std::shared_ptr<Base> ptr_shared = std::make_shared<Derived>();
    shared_derived_ptr_list.push_back(ptr_shared);

    // experimenting with list of unique_ptr
    //std::unique_ptr<Base> ptr_unique = std::make_unique<Derived>();
    //unique_derived_ptr_list.push_back(ptr_unique);  // This line will causes a compile error
    //unique_derived_ptr_list.push_back(std::move(ptr_unique));  // although move semantics do work on it

    // Subquestion (b)
    // Using a factory function to create instances of Derived and then adding them to the list
    // for the shared_ptr list
    for (int j = 0; j < 4; ++j)
    {
        shared_derived_ptr_list.push_back(createBase());
    }

    // Subquestion (c)
    // testing the print functionlity
    for (auto ele : shared_derived_ptr_list) {
        ele->print();
    }

    std::cout << "number of derived objects on the shared_derived_ptr_list: " << shared_derived_ptr_list.size() << std::endl;

    /*
    * we are sure that there are no memory leaks since there are 5 Derived objects dynamically allocated on the
    * heap. And we can see that the constructor and destructor for the Derived (and thus the Base) 
    * are also being called 5 times.
    * 
    * This means that there is no memory leak; and all the objects which are created via the factor fucntion are destroyed.
    */

    return 0;
}
