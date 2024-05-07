#include <iostream>
#include <vector>

// first Subquestion
class Foo {
public:
    int x;
    Foo() : x(0) { std::cout << "Default constructor\n"; } // Default constructor
    Foo(int x) : x(x) { std::cout << "Parameterised constructor\n"; } // Parameterised constructor
    Foo(const Foo& other) : x(other.x) { std::cout << "Copy constructor\n"; } // Copy constructor
    // Move constructor
    Foo(Foo&& other) noexcept : x(std::move(other.x)) {
        std::cout << "Move constructor\n";
        other.x = 0; // Reset the moved-from object
    }

    // Move assignment operator
    Foo& operator=(Foo&& other) noexcept {
        if (this != &other) {
            x = std::move(other.x);
            std::cout << "Move assignment operator\n";
            other.x = 0; // Reset the moved-from object
        }
        return *this;
    }
};  

// Third Subquestion:
struct S
{
    int x;
    struct Foo
    {
        int i; int j; int a[3];
    } b;
};

int main() {
    // Default initialisation - no initilization value provided
    std::cout << "Foo a; calls: ";
    Foo a;

    // Value initialisation - empty initializer 
    std::cout << "Foo b{}; calls: ";
    Foo b{};

    // Direct initialisation - 10 give as an explicit argument
    std::cout << "Foo c(10); calls: ";
    Foo c(10);

    // Copy initialisation - object d created as a copy of object c
    std::cout << "Foo d(c); calls: ";
    Foo d(c);

    // List initialisation
    std::cout << "Foo e{ 20 }; calls: ";
    Foo e{ 20 };
    // if the constructor had other parameters, we would give them as:
    // Foo e{ 20 ,10.6, vec}; etc.

    // Aggregate initialisation
    struct Aggregate {
        int x, y;
    };
    Aggregate f = { 1, 2 };

    // Reference initialisation - changes to object a will be reflected in object g as well
    std::cout << "Foo& g = a; calls: ";
    Foo& g = a;
    // nothing printed.. no new object actually created .. reference assigned
    std::cout << "\n";

    std::cout << "Foo h = std::move(a); calls: ";
    Foo h = std::move(a);

    std::cout << "Foo&& i = std::move(h); calls: ";
    Foo&& i = std::move(h);
    // nothing printed.. no new object actually created .. reference assigned

    /*
    * Subquestion (b): ill formed cases for the various ways to initialize an object:
    * Default initialisation: If a class doesn’t have a default constructor (or if it is deleted), 
    * trying to default initialise an object of that class will result in a compile error.
    * 
    * Value initialisation: Similar to default initialisation, if a class doesn’t have a default constructor (or if deleted), 
    * trying to value initialise an object of that class will result in a compile error.
    * 
    * Direct initialisation: If the constructor parameters don’t match the arguments provided during direct initialisation, 
    * it will result in a compile error.
    * 
    * Copy initialisation: If a class doesn’t have a copy constructor (or if deleted), 
    * trying to copy initialise an object of that class will result in a compile error.
    * 
    * List initialisation: If the class isn’t designed to support list initialisation 
    * (i.e., it doesn’t have a constructor that takes an std::initializer_list), 
    * trying to list initialise an object of that class will result in a compile error.
    * 
    * Aggregate initialisation: This only works with aggregate types.
    * Trying to aggregate initialise a non-aggregate type will result in a compile error.
    * 
    * Reference initialisation: If you try to bind a non-const lvalue reference to an rvalue, 
    * or if the types of the reference and the object aren’t compatible, it will result in a compile error.
    */

    // Third Subquestion:
    S s_obj = { 5, {3, 4, {7, 8, 9}} };


    // Fourth Subquestion:
    // default initilization:
    S s1;

    // value initialization:
    S s2{};

    // Direct initialization;
    // List/Uniform initialization;
    // Aggregate initialization
    // all three approaches have the same syntax in this case:
    S s3 = { 7, {8, 9, {10, 11, 12}} };

    // Copy initialization
    S s4 = s3;

    return 0;
}