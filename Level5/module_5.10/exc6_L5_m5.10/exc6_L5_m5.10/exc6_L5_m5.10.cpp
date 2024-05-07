#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iostream>

using namespace boost::numeric::ublas;

int main()
{
    // Subquestion (a)
    // creating a 4x4 matrix and initializing
    matrix<double> m(4, 4);
    for (unsigned i = 0; i < m.size1(); ++i)
        for (unsigned j = 0; j < m.size2(); ++j)
            m(i, j) = 10 * i + j;

    std::cout << "matrix m: " << m << std::endl;

    // matrix_row
    matrix_row<matrix<double>> mr(m, 1);
    std::cout << "Matrix Row (row 1): " << mr << std::endl;

    // matrix_column
    matrix_column<matrix<double>> mc(m, 2);
    std::cout << "Matrix Column (column 2): " << mc << std::endl;

    // matrix_range
    matrix_range<matrix<double>> mrng(m, range(1, 3), range(1, 3));
    std::cout << "Matrix Range (submatrix 1-2, 1-2): " << mrng << std::endl;

    // matrix_slice
    matrix_slice<matrix<double>> ms(m, slice(0, 2, 2), slice(0, 2, 2)); // picking 2x2 top-left corner
    std::cout << "Matrix Slice (2x2 from top-left, stride 2): " << ms << std::endl;
   
    // Subquestion (b)
    // initilializing a matrix
    matrix<double> mtrix(3, 3);
    int count = 1;
    for (unsigned i = 0; i < mtrix.size1(); ++i)
        for (unsigned j = 0; j < mtrix.size2(); ++j)
            mtrix(i, j) = count++;

    std::cout << "\nmtrix: " << mtrix << std::endl;

    // defining the matrix slice
    matrix_slice<matrix<double>> mslice(mtrix, slice(0, 1, 3), slice(0, 1, 3));

    // printing the elements of the matrix slice
    std::cout << "Matrix Slice elements: " << mslice << std::endl;

    // because the Size is 1, the Stride essentially doesn't affect the output 
    // since there's no second element to apply a stride to
    // this leads to our unexpected result of all the elements being printed
    // had the matrix size been greater than the stride, we would get a subset of mtrix

    return 0;
}