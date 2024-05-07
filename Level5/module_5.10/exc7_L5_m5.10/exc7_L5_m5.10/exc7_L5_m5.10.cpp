#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iostream>
#include <cmath>

void vector_products() {
    using namespace boost::numeric::ublas;
    vector<double> u(3), v(3);
    u(0) = 1; u(1) = 2; u(2) = 3;
    v(0) = 4; v(1) = 5; v(2) = 6;

    std::cout << "\nvector v: " << v << std::endl;
    std::cout << "\nvector u: " << u << std::endl;

    // inner product
    double inner = inner_prod(u, v);
    std::cout << "Inner product: " << inner << std::endl;

    // outer product
    matrix<double> outer = outer_prod(u, v);
    std::cout << "Outer product:\n" << outer << std::endl;
}

void vector_addition_subtraction() {
    using namespace boost::numeric::ublas;
    vector<double> a(3), b(3);
    a(0) = 1; a(1) = 2; a(2) = 3;
    b(0) = 4; b(1) = 5; b(2) = 6;

    std::cout << "\nvector a: " << a << std::endl;
    std::cout << "\nvector b: " << b << std::endl;

    // addition
    vector<double> sum = a + b;
    std::cout << "Sum: " << sum << std::endl;

    // subtraction
    vector<double> diff = a - b;
    std::cout << "Difference: " << diff << std::endl;
}

void vector_norms() {
    using namespace boost::numeric::ublas;
    vector<double> x(3);
    x(0) = -1; x(1) = 2; x(2) = -3;

    std::cout << "\nvector x: " << x << std::endl;

    // euclidean norm
    double euclidean = norm_2(x);
    std::cout << "Euclidean norm: " << euclidean << std::endl;

    // L1 norm
    double l1 = norm_1(x);
    std::cout << "L1 norm: " << l1 << std::endl;

    // max norm
    double max_norm = norm_inf(x);
    std::cout << "Max norm: " << max_norm << std::endl;
}

void matrix_norms() {
    using namespace boost::numeric::ublas;
    matrix<double> m(2, 2);
    m(0, 0) = -1; m(0, 1) = 2;
    m(1, 0) = 3;  m(1, 1) = -4;

    std::cout << "\nmatrix m: " << m << std::endl;

    // L1 norm
    double l1_norm = norm_1(m);
    std::cout << "L1 norm of matrix: " << l1_norm << std::endl;

    // max norm
    double max_norm = norm_inf(m);
    std::cout << "Max norm of matrix: " << max_norm << std::endl;
}

void matrix_vector_product() {
    using namespace boost::numeric::ublas;
    matrix<double> m(2, 3);
    vector<double> v(3);
    m(0, 0) = 1; m(0, 1) = 2; m(0, 2) = 3;
    m(1, 0) = 4; m(1, 1) = 5; m(1, 2) = 6;
    v(0) = 1; v(1) = 2; v(2) = 3;

    std::cout << "\nmatrix m: " << m << std::endl;
    std::cout << "\nvector v: " << v << std::endl;

    // matrix-vector product
    vector<double> result = prod(m, v);
    std::cout << "Matrix-vector product: " << result << std::endl;
}


int main()
{
    // testing
    vector_products();
    vector_addition_subtraction();
    vector_norms();
    matrix_norms();
    matrix_vector_product();
    return 0;
}
