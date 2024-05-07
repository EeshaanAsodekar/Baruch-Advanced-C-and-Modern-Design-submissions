#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <type_traits>

//  Emulating deprecated C++ 98 STL Bind Code using lambda functions
template <typename T>
std::function<T(const T&)> bind1st(const std::function<T(const T& x, const T& y)>& f, T&& x_)
{ 
    // Bind to the first param x of f(x,y)
    return [=](double y)
        {
           return f(x_,y);
        };
}

template <typename T>
std::function<T(const T&)> bind2nd(const std::function<T(const T& x, const T& y)>& f, T&& y_)
{
    // Bind to the second param y of f(x,y)
    return [=](double x)
        {
            return f(x, y_);
        };
}

int main() {
    // Define a function of arity 2
    auto fxy = [](double x, double y){
        return x * y;
    };

    auto fx = bind1st<double>(fxy, 10.0); // arity 1
    auto fy = bind2nd<double>(fxy, 30.0); // arity 1

    std::cout << "fxy(10,3.0) or fx(3.0): " << fx(3.0) << std::endl;
    std::cout << "fxy(10,30) or fx(10): " << fy(10) << std::endl;
    
    std::vector<double> vec(10, 2.0);
    std::transform(vec.begin(), vec.end(), vec.begin(), fx);
    for (auto i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << ",";
    }

    return 0;
}
