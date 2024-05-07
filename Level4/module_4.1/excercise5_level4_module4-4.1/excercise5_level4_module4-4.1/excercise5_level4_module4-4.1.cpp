#include <iostream>
#include "Vector.h"

int main()
{
    Vector<int, 4> myVector(10);myVector[1] = 100;myVector[3] = 200;
    std::cout << "myVector:" << std::endl;
    myVector.print();

    // Subquestion (a): Iterators for Vector
    // testing iterators:
    std::cout << "iterating over myVector:\n";

    // iterator
    for (auto itr = myVector.begin();itr != myVector.end();itr++) {
        std::cout << *itr << "\t";
    }
    std::cout << std::endl;

    // constant iterator
    for(auto itr = myVector.cbegin();itr != myVector.cend();itr++) {
        std::cout << *itr << "\t";
    }
    std::cout << std::endl;

    // changing values of myVector via iterator
    std::cout << "adding 100 to all the elements of myVector using iterator" << std::endl;

    for (auto itr = myVector.begin();itr != myVector.end();itr++) {
        *itr += 100;
    }

    myVector.print();

    // Subquestion (a) : testing wrappers for the STL inner_product functions
    // Subquestion (b) : test the first variant
    // testing first variant of inner_product
    Vector<double, 3> vec1(1.0), vec2(2.0);

    std::cout << "\nvec1:";
    vec1.print();

    std::cout << "\nvec2:";
    vec2.print();

    std::cout << "\ninner_product(vec1, vec2, 0.0) : " << inner_product(vec1, vec2, 0.0) << std::endl;  // Output: 6

    // Subquestion (c): For the second variant, test it using addition and multiplication operators
    // testing second variant of inner_product
    BinaryFunction<double> add = [](double a, double b) { return a + b; };
    BinaryFunction<double> mul = [](double a, double b) { return a * b; };
    
    // 0.0 + 1*2 + 1*2 + 1*2 = 6
    std::cout << "\ninner_product(vec1, vec2, 0.0, add, mul) : " << inner_product(vec1, vec2, 0.0, add, mul) << std::endl;  // Output: 6
    
    // 0.0 * (1+2) * (1+2) * (1+2) = 0
    std::cout << "\ninner_product(vec1, vec2, 0.0, mul,add) : " << inner_product(vec1, vec2, 0.0, mul, add) << std::endl;  // Output: 0
    
    // 0.0 * (1*2) * (1*2) * (1*2) = 0
    std::cout << "\ninner_product(vec1, vec2, 0.0, mul, mul) : " << inner_product(vec1, vec2, 0.0, mul, mul) << std::endl;  // Output: 0
    
    // 0.0 + (1+2) + (1+2) + (1+2) = 9
    std::cout << "\ninner_product(vec1, vec2, 0.0, add, add) : " << inner_product(vec1, vec2, 0.0, add, add) << std::endl;  // Output: 9

    // Subquestion (d) outer product
    auto outerProduct = outer_product(vec1, vec2);
    std::cout << "\nouter_product(vec1, vec2): " << std::endl;
    printMatrix(outerProduct);

    // Subquestion (e) complex vectors outer product
    Vector<std::complex<double>, 3> vecCompx1(std::complex<double>(1.0, 1.0)), vecCompx2(std::complex<double>(2.0, -2.0));
    auto outerProductC = outer_product(vecCompx1, vecCompx2);
    std::cout << "\nouter_product(vecCompx1, vecCompx2): " << std::endl;
    printMatrixC(outerProductC);

    return 0;
}
