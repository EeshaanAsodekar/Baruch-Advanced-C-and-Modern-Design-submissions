#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iostream>
#include <algorithm>
#include <functional>

namespace ublas = boost::numeric::ublas;

int main()
{
    // Subquestion (a)
    int size = 5;
    ublas::vector<double> v1(size);

    // using the indexing operators () and [] to access the elements of the vector
    for (int i = 0; i < size; ++i) {
        v1(i) = i + 1.0;  
        v1[i] = i * 2.0;  
    }

    std::cout << "Vector v1: " << v1 << std::endl;

    // Subquestion (b)
    ublas::vector<double> v2(size);

    for (int i = 0; i < size; ++i) {
        v2[i] = 2.0;
    }

    std::cout << "Vector v2: " << v2 << std::endl;

    v1 += v2;  // v1 = v1 + v2
    std::cout << "(v1 += v2)    Vector v1: " << v1 << std::endl;

    v1 *= 2.5; // v1 = v1 * 2.5
    std::cout << "(v1 *= 2.5)   Vector v1: " << v1 << std::endl;

    v1 -= v2; // v1 = v1 - v2
    std::cout << "(v1 -= v2)    Vector v1: " << v1 << std::endl;

    // Subquestion (c)

    ublas::vector<double> v3(size);
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::multiplies<>());

    std::cout << "Vector v3 after v1 std::multiplies<>() v2: " << v3 << std::endl;

    v1 -= v3; // v1 = v1 - v3
    std::cout << "(v1 -= v3)    Vector v1: " << v1 << std::endl;

    // Subquestion (d)
    ublas::vector<double> scalar_vector(100, 5.0);
    std::cout << "Scalar vector: " << scalar_vector << std::endl;


    return 0;
}