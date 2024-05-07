#include <iostream>
#include <vector>
#include "C.h"

using namespace std;

int main()
{
    C Cobj1;
    
    vector<int> myvec{ 1,2,3,4 };
    vector<int> myvec2{ 2,4,6,8 };

    Cobj1.print();

    Cobj1.modify_vec(myvec);

    Cobj1.print();

    //C Cobj2(Cobj1);

    C Cobj2;

    //Cobj2 = Cobj1;
    //keyword 'delete' used on the assignment operator; the above line will give an error

    //C Cobj3 = myvec2;
    // implicit conversion no longer works
    C Cobj3(myvec2);

    Cobj3.print();

    //C Cobj4({1,2,3});
    //Cobj4.print();

    C Cobj4;
    constexpr int myarr3[] = {3,6,9,12};
    Cobj4.modify_vec(myarr3, 4);
    Cobj4.print();

    return 0;
}

/*
* Excercise 1 answers:
* 
* (a) once we use the keyword default explicitly on the default constructor and
* we use the keyword delete to mark the copy constructor and the assignment operator as deleted fuctions,
* this was resulting behaviour was observed:
* 1. we can still use the default constructor wihtout any qualms;
* 2. we can no longer use the deleted copy constructor and the assignment operator as we did before 
* if we try to use the copy consturctor, we get this error: 'C &C::C(const C &)': attempting to reference a deleted function	
* if we try to use the assignment operator, we get this error: 'C &C::operator =(const C &)': attempting to reference a deleted function		
* 
* (b) I defined a constructor with parameters for the C class to demonstrate the effect of the explicit keyword on a constructor
* before adding the explicit keyword: C Cobj3 = myvec2; works
* after adding the explicit keyword: C Cobj3 = myvec2; no longer works, compiler throws an error
* the error is:'initializing': cannot convert from 'std::vector<int,std::allocator<int>>' to 'C'
* instead we now have to define Cobj3 as: C Cobj3(myvec2); which works
* 
* (c) we cannot constexpr the constructor with parameter or even the myvec and myvec2 because std::vector allocates memory at runtime
* but, we can make the modify_vec2() setter function constexpr 
* we use constexpr int myarr3[] as input to the constexpr setter fucntion modify_vec2()
* we can do this since the argument of the fuction (myarr3) is known at compile time; then the i/p arguments of the 
* modify_vec2() fucntion are also known at compile time
* 
* (d) generally speaking, any of the member fuctions that contain operations such as memory allocation or file I/O, then that
* member fuction can potentially throw exceptions. This is the logic on the basis of which we will use the keyword noexcept
* in more complex classes which use the operations mentined above. In our case, the member fuctions print() and scale_to_double()
* are gauranteed not to throw exceptions, hence the noexcept keyword is used when declaring and defining them.
*/