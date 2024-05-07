#include <iostream>
#include <type_traits>
#include <vector>
#include <string>
#include <array>

class Car {
public:
    std::string brand;
    std::string model;
    int year;
};


int main()
{
    // Subquestion (a)
    std::cout << std::boolalpha;
    // fundamental types
    std::cout << "int: " << std::is_array<int>::value << '\n';
    std::cout << "double: " << std::is_array<double>::value << '\n';
    std::cout << "char: " << std::is_array<char>::value << '\n';
    // Scalar types
    enum Color { red, green, blue };
    std::cout << "Color: " << std::is_array<Color>::value << '\n';
    // object types
    std::cout << "Car: " << std::is_array<Car>::value << '\n';
    // compound types
    std::cout << "int[3]: " << std::is_array<int[3]>::value << '\n';
    std::cout << "double[4][5]: " << std::is_array<double[4][5]>::value << '\n';
    std::cout << "std::vector<int>: " << std::is_array<std::vector<int>>::value << '\n';
    std::cout << "std::array<int, 3>: " << std::is_array<std::array<int, 3>>::value << '\n';

    std::cout << "\n\nSubquestion(b)\narray being evaluated: int[][2][3][4]\n";

    // Subquestion (b)
    std::cout << "rank<int[][2][3][4]>: " << std::rank<int[][2][3][4]>::value << std::endl;
    std::cout << "extent<int[][2][3][4], 0>: " << std::extent<int[][2][3][4], 0>::value << std::endl;
    std::cout << "extent<int[][2][3][4], 1>: " << std::extent<int[][2][3][4], 1>::value << std::endl;
    std::cout << "extent<int[][2][3][4], 2>: " << std::extent<int[][2][3][4], 2>::value << std::endl;
    std::cout << "extent<int[][2][3][4], 3>: " << std::extent<int[][2][3][4], 3>::value << std::endl;

    std::cout << "\n\nSubquestion(c)\narray being evaluated: int[][2][3][4]\n";

    // Subquestion (c)
    typedef std::remove_extent<int>::type A; // remains an int
    typedef std::remove_extent<int[]>::type B; // int
    typedef std::remove_extent<int[][2]>::type C; // int[2]
    typedef std::remove_extent<int[][2][3]>::type D; // int[2][3]
    typedef std::remove_extent<int[][2][3][4]>::type E; // int [2][3][4]
    typedef std::remove_all_extents<int[][2][3][4]>::type F;// int

    std::cout << "rank<A>: " << std::rank<A>::value << std::endl;
    std::cout << "rank<B>: " << std::rank<B>::value << std::endl;
    std::cout << "rank<C>: " << std::rank<C>::value << std::endl;
    std::cout << "rank<D>: " << std::rank<D>::value << std::endl;
    std::cout << "rank<E>: " << std::rank<E>::value << std::endl;
    std::cout << "rank<F>: " << std::rank<F>::value << std::endl;

    std::cout << "F same as int: " << std::is_same<int, F>::value << std::endl;

    /*Answer to Subquestion (c)
    * when we use std::remove_extent on a multidimentional array in C++ it removes it first dimention
    * and leave us with the rest of the dimentions with the same extents as before
    * 
    * for example, typedef std::remove_extent<int[10][20][30]>:: type X
    * will make X int[20][30]
    * 
    * also, std::remove_all_extents essentially just gives us a scalar of the type of the arrays underlying type
    * because it removes all the dimentions of the multidimentional array which we give as input
    */

    return 0;
}
