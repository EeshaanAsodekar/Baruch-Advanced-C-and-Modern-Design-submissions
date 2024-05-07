#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <complex>
#include <iostream>

namespace ublas = boost::numeric::ublas;
using complex =  std::complex<double>;

int main()
{
    // Subquestion (a) create and manipulate a sparse matrix of complex numbers
    ublas::compressed_matrix<complex> sparseMatrix(4, 4, 10);
    sparseMatrix(0, 1) = complex(2.0, 3.0); 
    sparseMatrix(1, 1) = complex(5.0, 1.0); 
    sparseMatrix(2, 2) = complex(4.0, 0.0);
    sparseMatrix(2, 3) = complex(4.0, 70.0);
    sparseMatrix(3, 3) = complex(4.0, 50.0);

    std::cout << "Sparse Matrix:\n" << sparseMatrix << std::endl;

    sparseMatrix.erase_element(1, 1); 
    std::cout << "Sparse Matrix after clearing element 1,1 :\n" << sparseMatrix << std::endl;

    sparseMatrix.clear();
    std::cout << "Sparse Matrix after clearning:\n" << sparseMatrix << std::endl;

    // Subquestion (b) 
    ublas::triangular_matrix<double, ublas::lower, ublas::row_major> lowerTriMatrix(3, 3);
    ublas::triangular_matrix<double, ublas::upper, ublas::column_major> upperTriMatrix(3, 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j <= i; ++j) {
            lowerTriMatrix(i, j) = i + j + 1; 
        }
        for (int j = i; j < 3; ++j) {
            upperTriMatrix(i, j) = i + j + 1; 
        }
    }

    std::cout << "Lower Triangular Matrix (Row-major):\n" << lowerTriMatrix << std::endl;
    std::cout << "Upper Triangular Matrix (Column-major):\n" << upperTriMatrix << std::endl;


    // Subquestion (c) upper and lower triangular views of a dense matrix
    try {
        ublas::matrix<double> denseMatrix(4, 4);
        for (unsigned i = 0; i < denseMatrix.size1(); ++i)
            for (unsigned j = 0; j < denseMatrix.size2(); ++j)
                denseMatrix(i, j) = i * 4 + j + 1;

        ublas::triangular_adaptor<ublas::matrix<double>, ublas::lower> lowerView(denseMatrix);
        ublas::triangular_adaptor<ublas::matrix<double>, ublas::upper> upperView(denseMatrix);

        std::cout << "Dense Matrix:\n" << denseMatrix << std::endl;

        std::cout << "Lower Triangular View of Dense Matrix:\n" << lowerView << std::endl;
        std::cout << "Upper Triangular View of Dense Matrix:\n" << upperView << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
