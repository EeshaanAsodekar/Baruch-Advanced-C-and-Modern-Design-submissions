#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iostream>

namespace ublas = boost::numeric::ublas;

int main()
{
    // Subquestion(a) Create matrices with various template parameters
    // Matrix with dynamic storage and double data type, row-major
    ublas::matrix<double, ublas::row_major> matA(3, 4,1.00);
    // Matrix with dynamic storage and int data type, column-major
    ublas::matrix<int, ublas::column_major> matB(4, 3);

    // Matrix with bounded storage, double data type, row-major
    ublas::bounded_matrix<double, 2, 2, ublas::row_major> matFixed(2, 2);
    matFixed(0, 0) = 1.5;
    matFixed(0, 1) = 2.5;
    matFixed(1, 0) = 3.5;
    matFixed(1, 1) = 4.5;

    // Matrix with unbounded storage and float data type, column-major
    ublas::matrix<float, ublas::column_major> matFloat(3, 3);
    for (int i = 0; i < matFloat.size1(); ++i) {
        for (int j = 0; j < matFloat.size2(); ++j) {
            matFloat(i, j) = i * 3.0f + j;
        }
    }

    // and various other combinations are possible

    // Subquestion (b) Access and modify elements using operator ()
    matA(0, 0) = 1.0;
    matA(0, 1) = 2.0;
    matA(1, 0) = 3.0;
    matA(1, 1) = 4.0;
    std::cout << "Matrix A:\n" << matA << std::endl;

    // Subquestion (c) Add and subtract matrices (need same dimension and type)
    ublas::matrix<double, ublas::row_major> matC(3, 4, 2.0);  // another 3x4 matrix
    matA += matC;  // add matC to matA
    matA -= matC;  // subtract matC from matA
    std::cout << "Matrix A after add and subtract:\n" << matA << std::endl;

    // Subquestion (d) Resize a matrix
    matA.resize(5, 5, true); // resize matA to 5x5, preserve elements ... added zeros
    std::cout << "Matrix A after resizing:\n" << matA << std::endl;

    // Subquestion (e) create zero and indentity matrices
    ublas::matrix<double> zeroMatrix(3, 5, 0.0);
    ublas::identity_matrix<double> identityMatrix(4);  // 4x4 identity matrix
    
    std::cout << "Zero Matrix:\n" << zeroMatrix << std::endl;

    std::cout << "Identity Matrix:\n" << identityMatrix << std::endl;


    return 0;
}
