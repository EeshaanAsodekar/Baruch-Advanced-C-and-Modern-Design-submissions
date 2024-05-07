#include <iostream>
#include <type_traits>

template <typename T>
void IsPointer(const T& t)
{ 
    if (std::is_pointer<decltype(t)>::value)
    {
        std::cout << "This is a pointer type argument\n";
    }
    else
    {
        std::cout << "_not_ a pointer type argument\n";
    }
}

template <typename T>
void IsNullPointer(const T& t)
{
    if (std::is_null_pointer<decltype(t)>::value)
    {
        std::cout << "This is a null pointer type argument\n";
    }
    else
    {
        std::cout << "_not_ a null pointer type argument\n";
    }
}

template <typename T>
void IsLvalueReference(T&& t)
{
    if (std::is_lvalue_reference<std::remove_reference_t<decltype(t)>>::value)
    {
        std::cout << "This is a lvalue refernce type argument\n";
    }
    else
    {
        std::cout << "_not_ a lvalue reference type argument\n";
    }
}

template <typename T>
void CheckIfRvalueReference(T&& t)
{
    if (std::is_rvalue_reference<T>::value)
    {
        std::cout << "This is an rvalue reference type argument\n";
    }
    else
    {
        std::cout << "This is _not_ an rvalue reference type argument\n";
    }
}

template <typename T>
void CheckIfLvalueReference(const T&& t)
{
    if (std::is_lvalue_reference<T>::value)
    {
        std::cout << "This is an lvalue reference type argument\n";
    }
    else
    {
        std::cout << "This is _not_ an lvalue reference type argument\n";
    }
}

int main()
{

    int x = 10;
    int& ref = x;
    int&& erref = 20;

    std::cout << "Checking ref:\n";
    CheckIfRvalueReference<int&>(ref);

    CheckIfRvalueReference<int&&>(erref);

    return 0;
}

