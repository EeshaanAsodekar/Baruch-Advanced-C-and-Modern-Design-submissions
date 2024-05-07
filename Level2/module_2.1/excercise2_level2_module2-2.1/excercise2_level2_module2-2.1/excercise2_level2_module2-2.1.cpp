// excercise2_level2_module2-2.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <type_traits>

// printer fucntion when the input
// is a pointer type
template <typename T>
void printer(const T& t, std::true_type) {
    std::cout << "printing pointer: ";
    std::cout << *t << std::endl;
}

// printer fucntion implementation when the input
// is a scalar reference type
template <typename T>
void printer(const T& t, std::false_type) {
    std::cout << "printing scalar reference type: ";
    std::cout << t << std::endl;
}

// print fucntion which supports both pointers and scalar reference types
// print_pointer_or_reference is the main fucntion
template <typename T>
void print_pointer_or_reference(const T& t)
{ 
    // on the basis of the output of std::is_pointer<T>()
    // it is directed to the scalar reference printer or the pointer printer
    printer(t, std::is_pointer<T>());
}

int main()
{
    // scalar reference input
    int x = 10;

    // pointer input
    int* int_ptr = new int(100);

    print_pointer_or_reference(x); // calls printer(const T& t, std::false_type) from the print_pointer_or_reference
    print_pointer_or_reference(int_ptr); // calls printer(const T& t, std::true_type) from the print_pointer_or_reference

    return 0;
}

