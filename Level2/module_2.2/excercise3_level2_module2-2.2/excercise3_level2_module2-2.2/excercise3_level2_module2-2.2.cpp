// excercise3_level2_module2-2.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <type_traits>
#include <tuple>

// Subquestion (a)
// mapping between signed and unsiged ints 
std::make_unsigned<int>::type intToUnsigned(int& num) {
    return static_cast<std::make_unsigned<int>::type>(num);
}

std::make_signed<unsigned int>::type unsignedToInt(unsigned int num) {
    return static_cast<std::make_signed<unsigned int>::type>(num);
}

// Adding/removing the const specifier to or from a type
// Add the const specifier to a type
template<typename T>
const T& addConst(T& value) {
    return value;
}

// Remove the const specifier from a type using std::remove_const
template<typename T>
typename std::remove_const<T>::type removeConst(const T& value) {
    return value;
}


// adding a pointer to a type
template<typename T>
typename std::add_pointer<T>::type addPointer(T& value) {
    return &value;
}

// removing a pointer from a type
template<typename T>
typename std::remove_pointer<T>::type removePointer(T* value) {
    return *value;
}

// Add the volatile specifier to a type
template<typename T>
typename std::add_volatile<T>::type& addVolatile(T& value) {
    return value;
}

// Remove the volatile specifier from a type using std::remove_volatile
template<typename T>
typename std::remove_volatile<T>::type removeVolatile(volatile T& value) {
    return value;
}

// for CTAD example
template <typename T1, typename T2>
class MyPair {
public:
    T1 first;
    T2 second;
    MyPair(T1 first, T2 second) : first(first), second(second) {}
};

float dummyFunction(const float& x) { return x; };

int main()
{
    int value = -10;
    // Test for intToUnsigned and unsignedToInt
    unsigned int unsignedValue = intToUnsigned(value);
    std::cout << "Unsigned version of " << value << " is " << unsignedValue << std::endl;
    std::cout << "Signed version of " << unsignedValue  << " is " << unsignedToInt(unsignedValue) << std::endl;

    // Test for addConst
    auto& constValue = addConst(value);
    std::cout << "Is constValue const? " << std::boolalpha << std::is_const<std::remove_reference<decltype(constValue)>::type>::value << std::endl;

    // Test for removeConst
    auto nonConstValue = removeConst(constValue);
    std::cout << "Is nonConstValue const? " << std::boolalpha << std::is_const<std::remove_reference<decltype(nonConstValue)>::type>::value << std::endl;

    // Test for addPointer
    auto pointerValue = addPointer(value);
    std::cout << "Pointer version of " << value << " is " << pointerValue << std::endl;

    // Test for removePointer
    auto dereferencedValue = removePointer(pointerValue);
    std::cout << "Dereferenced version of " << pointerValue << " is " << dereferencedValue << std::endl;

    // Test for addVolatile
    auto& volatileValue = addVolatile(value);
    std::cout << "Is volatileValue volatile? " << std::boolalpha << std::is_volatile<std::remove_reference<decltype(volatileValue)>::type>::value << std::endl;

    // Test for removeVolatile
    auto nonVolatileValue = removeVolatile(volatileValue);
    std::cout << "Is nonVolatileValue volatile? " << std::boolalpha << std::is_volatile<decltype(nonVolatileValue)>::value << std::endl;


    // examples for CTAD:
    // Without CTAD
    std::tuple<int, float, std::string> t1 = std::make_tuple(10, 2.5f, "Hello");

    // With CTAD
    std::tuple t2(10, 2.5f, "Hello"); // The compiler deduces the types

    // Without CTAD
    MyPair<int, std::string> p1 = MyPair<int, std::string>(10, "Hello");

    // With CTAD
    MyPair p2(10, "Hello"); // The compiler deduces the types


    // investigating applicability of declatype and std::is_same 
    // decltype and std::is_same can be used together to compare the type of a result with a target type.
    float f = 0.0f;

    // using decltype to get the type of the expression dummyFunction(f)
    auto result = dummyFunction(f);

    // using std::is_same to compare the type of result with float
    if (std::is_same<decltype(result), float>::value) {
        std::cout << "The type of result is float." << std::endl;
    }
    else {
        std::cout << "The type of result is not float." << std::endl;
    }

    /*
    * This way, we can compare the type of any expression or variable with a target type. 
    * This can be useful in template metaprogramming, for example, where we might need to perform different actions based 
    * on the type of a template argument. 
    * It’s also useful when we want to ensure that a certain expression has the expected type, which can help catch bugs early.
    */

    return 0;
}

/* 
* Question) Discuss the difference between direct list initialisation and copy list initialisation in C++17/20 compared to C++11. 
* In which case does auto deduction reduce to std::initializer_list? Give a code example. 
* Under which circumstances can we get ill-formed expressions?
* 
* Differences: 
* In C++17, a significant change was made: given an enum-type with a fixed underlying size, 
* we can perform direct-list-initialization on it with a value of the underlying type. 
* But we cannot perform copy-list-initialization from such a value.
* In C++17/20, the rules for auto deduction from braced-init-list were also changed. 
* For copy list initialization, auto deduction will deduce a std::initializer_list<T> 
* if all elements in the list have the same type, or be ill-formed. 
* For direct list initialization, auto deduction will deduce a T if the list has a single element, 
* or be ill-formed if there is more than one element.
* 
* 
* Case where auto deduction reduces to std::initializer_list:
* In C++11/14, a special rule was introduced that auto variables which are initialized with a braced initializer 
* are deduced to be of type std::initializer_list<X>, where X is the type of the elements of the initializer/
* example: auto numbers = {1, 2, 3, 4, 5}; // numbers is of type std::initializer_list<int>
* 
* 
* Circumstances where we can get ill-formed expressions:
* A program that contains an integer literal that cannot be represented by any of the allowed types.
* A program that violates the One Definition Rule.
* A program that contains a diagnosable error such as passing the wrong number of arguments, or arguments which cannot be converted to the parameter types, or an overload ambiguity.
* A program that contains a violation of a rule for which no diagnostic is required.
*/

/*
* Question) Discuss how Class Template Argument Deduction (CTAD)) reduces code verbosity. 
* Give a non-trivial example using std::tuple and a user-defined class.
* 
* Class Template Argument Deduction (CTAD) is a feature introduced in C++17 that reduces code verbosity. 
* It allows the compiler to deduce class template arguments automatically, which can make the code more concise and easier to read
* 
* examples: refer main()
* 
*/
