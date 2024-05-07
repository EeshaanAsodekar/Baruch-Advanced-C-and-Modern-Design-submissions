#include <iostream>
#include <limits>

// Subquestion (a)
template <typename T>
T get_epsilon() {
    T epsilon = 1.0;
    while ((T(1.0) + T(0.5) * epsilon) != T(1.0))
    {
        epsilon *= 0.5;
    }

    return epsilon;
}

int main()
{
    // Subquestion (a)
    std::cout << "epsilon from the get_epsilon() function for float, double and long double: \n";
    std::cout << get_epsilon<float>() << std::endl; // 1.19209e-07
    std::cout << get_epsilon<double>() << std::endl; // 2.22045e-16
    std::cout << get_epsilon<long double>() << std::endl; // 2.22045e-16
    
    // Subquestion (b)
    std::cout << "\n\nepsilon from the std::numeric_limits<>::epsilon() for float, double and long double: \n";
    std::cout << std::numeric_limits<float>::epsilon() << std::endl; // 1.19209e-07
    std::cout << std::numeric_limits<double>::epsilon() << std::endl; // 2.22045e-16
    std::cout << std::numeric_limits<long double>::epsilon() << std::endl; // 2.22045e-16

    return 0;
}
