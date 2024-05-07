#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// depreciated Free/global function
[[deprecated("depreciated fucntion!")]] void print_vec(vector<double> vec) {
    for_each(vec.begin(), vec.end(), [](const double& x) -> void {cout << x << " ";});
}

// depreciated class
class [[deprecated("depreciated class!")]] test_class {
private:
    vector<double> vec;
public:
    test_class(vector<double> vec_) :vec(vec_) {}
    void print_vec() {
        for_each(vec.begin(), vec.end(), [](const double& x) -> void {cout << x << " ";});
    }
};

// class with depreciated member fucntion
class test_class2 {
private:
    vector<double> vec;
public:
    test_class2(vector<double> vec_) :vec(vec_) {}
    [[deprecated("depreciated member fucntion!")]] void print_vec() {
        for_each(vec.begin(), vec.end(), [](const double& x) -> void {cout << x << " ";});
    }
};

// depreciated global variable
[[deprecated("depreciated global varible x!")]]
int x = 10;

// depreciated enum and enumclass
enum [[deprecated("This enum is deprecated")]] OldEnum { A, B, C };
//enum OldEnum { A, B, C };

enum class [[deprecated("This enum class is deprecated")]] OldEnumClass { X, Y, Z };
//enum class OldEnumClass { X, Y, Z };

// depreciated template class specialization
template <typename T>
class MyClass {
public:
    void printMessage() {
        std::cout << "This is a member function of MyClass.\n";
    }
};

template <>
class [[deprecated("This specialization is deprecated")]]  MyClass<int> {
public:
    void printMessage() {
        std::cout << "This is a member function of the deprecated specialization of MyClass.\n";
    }
};

// depreciated lambda fucntion
[[deprecated("This lambda function is deprecated")]]
auto oldLambda = []()->void { cout << "Hello, World!\n"; };

int main()
{
    vector<double> vec{ 2.3,5.6,7.8 };

    /*
    * The [[deprecated]] attribute in C++ is intended to generate a warning, not an error, when the deprecated entity is used.
    * Some compilers or build systems are configured to treat all warnings as errors. 
    * This is often done to enforce a higher code quality standard. 
    * If our compiler is set to treat warnings as errors (often with a -Werror flag or similar), 
    * then using a deprecated entity will result in a compilation error; which is the case in the code below.
    */

    //print_vec(vec);
    // before marking the fucntion depreciated it printed onto the console:2.3,5.6,7.8 
    // after marking the function depreciated: Error C4996: 'print_vec': depreciated fucntion!
    
    //test_class test_obj(vec);
    //test_obj.print_vec();
    // before marking the test_class depreciated it printed onto the console:2.3,5.6,7.8 
    // after marking the test_class depreciated: 3 errors C4996
    // all error descriptions: 'test_class': depreciated class

    test_class2 test_obj2(vec);
    //test_obj2.print_vec();
    // before marking the print_vec member fucntion depreciated it printed onto the console:2.3,5.6,7.8 
    // after marking the print_vec member fucntion depreciated: 1 error C4996
    // error description: 'test_class2::print_vec': depreciated member fucntion!

    //cout << "global var x: " << x << endl;
    // before marking the global var x depreciated it printed onto the console:10
    // after marking the global var x depreciated:error C4996
    // 'x': depreciated global varible x!


    //OldEnum value = A;
    //cout << value;
    // before depreciating: prints 0 onto the console
    // after depreciating: error  description>'OldEnum': This enum is depreciated

    //OldEnumClass valueobj = OldEnumClass::X;
    // before depreciating: can work with this enum class variable
    // after depreciating: cannot even instantiate: error description>  'OldEnumClass':This enum class is depreciated

    // Using non-deprecated template class
    MyClass<double> myObject;
    myObject.printMessage();

    // Using deprecated template class specialization
    //MyClass<int> myDeprecatedObject;
    //myDeprecatedObject.printMessage();
    // after declaring this specialization as depreciated; the above two lines of code generate error C4996
    // error description: 'MyClass<int>': This specialization is deprecated
   

    // oldLambda();
    // after declaring the stored lambda fucntion as depreciated: 
    // error: C4996- 'oldLambda': This lambda function is deprecated

    return 0;
}
