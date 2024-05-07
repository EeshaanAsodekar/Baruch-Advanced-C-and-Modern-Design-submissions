#include <iostream>
#include <memory>

int main()
{
    // Define auto_ptr pointers instead of raw pointers
    std::auto_ptr <double> d(new double(1.0));

    // Dereference
    *d = 2.0;

    // Change ownership of auto_ptr
    // (after assignment, d is undefined)
    std::auto_ptr <double> d2 = d;
    // transfers the ownership of the memory pointed to by d to d2.
    // After this line, d becomes a null pointer

    *d2 = 3.0;

    //std::cout << "Auto values: " << *d.get() << ", " << *d2.get(); // commented out since this gives run time error
    // error because we are trying to print a dereferenced a null pointer
    /*
    * Subquestion (a): Type the above code and run it. Why does it give a run-time error?
    * When an std::auto_ptr is copied, ownership of the managed object is transferred to the new std::auto_ptr, 
    * and the original std::auto_ptr is set to a null pointer. 
    * This can leads to unexpected behavior, such as runtime errors when the original std::auto_ptr is dereferenced.
    * We experience this unexpected behaviour in the code snippet given in the question.
    * 
    * The auto_ptr's unusual copy semantics is why it was depriciated.
    */

    // Subquestion (b)
    // New version of the code:
    // Defining unique_ptr instead of std::auto_ptr
    std::unique_ptr<double> d_(new double(1.0));

    // Dereference
    *d_ = 2.0;

    // Change ownership of unique_ptr
    //std::unique_ptr<double> d2_ = d_;// unique_ptr does NOT allow copying 
    std::unique_ptr<double> d2_ = std::move(d_); // unique_ptr does allow ownership transfer via move semantics
    // d_ is now a null pointer
    *d2_ = 3.0;

    // Since d has been moved, we only print the value of d2
    std::cout << "Auto values (d2_ pointer): " << *d2_.get() << std::endl;
    // of course, trying to dereference and print d_ will also give a run time error over here as well

    return 0;
}