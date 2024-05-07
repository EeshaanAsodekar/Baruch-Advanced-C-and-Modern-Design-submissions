#include <iostream>
#include <functional>

// given
template <typename T>
using FunctionType = std::function<T(const T& t)>;

template <typename T>
using FunctionType2 = std::function<T(const T& t1, const T& t2)>;

// given
template <typename T>
void print(const FunctionType<T>& f, T t)
{
    std::cout << f(t) << '\n';
}
 
// given class
class C
{
    // Function object with extra member functions
private:
    double _data;
public:
    C(double data) : _data(data) {}

    double operator () (double factor) {
        return _data + factor;
    }

    double translate(double factor) {
        return _data + factor;
    }

    double translate2(double factor1, double factor2) {
        return _data + factor1 + factor2;
    }

    static double Square(double x) {
        return x * x;
    }
};

using namespace std;

int main()
{
    double input_data = 4.0, input_factor1 = 10.0, input_factor2 = 10.0;

    // binding the function wrapper to C's static member function
    FunctionType<double> f_Square = C::Square;

    C Cobj(input_data);
    // binding the function wrapper to C's member functions using std::bind and placeholders
    FunctionType<double> f_translate = bind(&C::translate, &Cobj, placeholders::_1);
    cout << f_translate(input_factor1) << endl;
    
    FunctionType<double> f_brac = bind(&C::operator(), &Cobj, placeholders::_1);
    cout << f_brac(input_factor1) << endl;

    // approach 1: designing a function wrapper which takes two double arguments as input
    FunctionType2<double> f_translate2_version1 = bind(&C::translate2, &Cobj, placeholders::_1, placeholders::_2);
    cout << f_translate2_version1(input_factor1,input_factor2) << endl;

    // approach 2: bind the first argument and keep the second as a placeholder
    // the member function then matches with FunctionType<double>
    auto intermediary = bind(&C::translate2, &Cobj, input_factor1, placeholders::_1);
    FunctionType<double> f_translate2_version2 = bind(intermediary, placeholders::_1);
    cout << f_translate2_version2(input_factor2) << endl;

    /*
    * expected output obtained.
    * Console Output:
    * 14
    * 14
    * 24
    * 24
    */

    return 0;
}
