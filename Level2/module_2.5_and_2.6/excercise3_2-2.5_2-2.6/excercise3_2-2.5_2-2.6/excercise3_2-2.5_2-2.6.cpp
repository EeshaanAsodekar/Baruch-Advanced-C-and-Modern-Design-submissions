#include <iostream>
#include <cmath>
#include <limits>
#include <boost/math/special_functions/next.hpp>

int main()
{
    // initializing some double variables to experiment on
    double a = 0.1;
    //double b = a + std::numeric_limits<double>::min();
    // min() is much smaller than the double's precision of 15 decimal points
    // with b variable initilized as the expression above, it is treated as a 0.1; i.e. same as a
    // this leads to find_distance(a,b) = 0 (the ULP)
    double b = a + 1e-15;

    std::cout.precision(std::numeric_limits<double>::max_digits10); 
    // we need to set the precision of cout to be able to notice the difference between a and b

    // Computing the next representable floating-point value after a
    double next_a = boost::math::float_next(a);
    std::cout << "The next representable value after " << a << " is " << next_a << std::endl;

    // Computing the next representable floating-point value before a
    double prev_a = boost::math::float_prior(a);
    std::cout << "The previous representable value before " << a << " is " << prev_a << std::endl;

    // Advance a by 10 ULP
    double advanced_a = boost::math::float_advance(a, 10);
    std::cout << "The value " << a << " advanced by 10 ULP is " << advanced_a << std::endl;

    // Computing the number of ULP (Units in Last Place) between a and b
    int ulp = boost::math::float_distance(a, b); // negative since a is smaller than b
    std::cout << "The number of ULP between " << a << " and " << b << " is " << ulp << std::endl;

    // Compute the next representable floating-point value after a in the direction of b
    double next_after_a_std = std::nextafter(a, b);
    double next_after_a_boost = boost::math::nextafter(a, b);
    std::cout << "The next representable value after " << a << " in the direction of " << b << " is " << next_after_a_std << std::endl;
    std::cout << "The next representable value after " << a << " in the direction of " << b << " is " << next_after_a_boost << std::endl;

    return 0;
}
