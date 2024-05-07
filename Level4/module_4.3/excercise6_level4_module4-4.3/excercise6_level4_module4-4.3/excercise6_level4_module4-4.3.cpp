#include <boost/random.hpp>
#include <iostream>

int main() {
    // Subquestion (a) create a variate of the triangle distribution
    // with lagged Fibonacci as random number engine.

    boost::random::lagged_fibonacci607 lfibo; // lagged Fibonacci random number engine
    boost::random::triangle_distribution<> triDist(0.0, 0.5, 1.0); // triangle distribution
    
    // a variate
    std::cout << "triangle dist variate: " << triDist(lfibo) << std::endl;

    // Subquestion (b) Use Boost function template generate_canonical()
    // experiment with various values of bits (for example, 8,16,32).
    std::cout << "Canonical variate (8 bits): " << boost::random::generate_canonical<double, 8>(lfibo) << std::endl;
    std::cout << "Canonical variate (16 bits): " << boost::random::generate_canonical<double, 16>(lfibo) << std::endl;
    std::cout << "Canonical variate (32 bits): " << boost::random::generate_canonical<double, 32>(lfibo) << std::endl;

    return 0;
}
