#include <iostream>
#include <vector>
#include "C.h"

using namespace std;

int main()
{
    C Cobj1;

    vector<int> myvec{ 1,2,3,4 };

    Cobj1.modify_vec(myvec);

    // Subquestion (b)
    cout << "before calling move constructor on Cobj1:\n";
    cout << "Cobj1:\n";
    Cobj1.print();
    // calling the move constructor 
    C Cobj2(move(Cobj1));
    cout << "\nC Cobj2(move(Cobj1)) performed!\n\n";

    cout << "after calling move constructor on Cobj1:\n";
    cout << "Cobj1:\n";
    Cobj1.print();
    cout << "Cobj2:\n";
    Cobj2.print();

    C Cobj3;

    cout << "\n\nbefore calling move assignment operator on Cobj1:\n";
    cout << "Cobj2:\n";
    Cobj2.print();
    // calling the assignment operator 
    Cobj3 = std::move(Cobj2);
    cout << "\nCobj3 = move(Cobj2);performed!\n\n";

    cout << "after calling assignment operator on Cobj1:\n";
    cout << "Cobj2:\n";
    Cobj2.print();
    cout << "Cobj3:\n";
    Cobj3.print();

    return 0;
}

/*
* Excercise 3 answers:
* (a) defined in C.h
* 
* (b) tested the move constructor and the move assignment operator in the main().
* to ensure that the move constructor is called instead of the copy constructor, we need to use std::move(); 
* eg. C Cobj2(move(Cobj1));
* this ensures that regardless of Cobj1 being a rvalue or an lvalue, the compiler treats it like an rvalue and
* and calls the move constructor
* 
* let us take another example, C Cobjy(Cobjx);
* if the Cobjx is an rvalue, then the move constructor will be called by default
* however, if Cobjx is an lvalue, then the copy consturctor will be called; unless we force using the std::move as we have above
* 
* 
* (c) if we use an lvalue as the source of an move operation, then the compiler will not use the move constructor or 
* the move assignment operator, even if they are defined. The copy constructor and the copy assignment operator will
* instead be called.
* As mentioned earlier, we can force the use of the move counterparts by telling the copiler to treat the 
* lvalue as a rvalue using std::move()
*/