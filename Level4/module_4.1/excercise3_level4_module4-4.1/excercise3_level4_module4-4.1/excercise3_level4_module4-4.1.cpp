#include <iostream>
#include <array>
#include <functional>
#include <algorithm>

template <typename V, int NR, int NC>
using NestedMatrix = std::array<std::array<V, NC>, NR>;

template <typename V, int NR, int NC>
class Matrix {
private:
    NestedMatrix<V, NR, NC> data;

public:
    // default constructor
    Matrix() :data{} {}

    // constructor with single numerical value as argument
    Matrix(V val) {
        for (auto& row : data) {
            row.fill(val);
        }
    }

    // copy constructor
    Matrix(const Matrix& mat) : data(mat.data) {}

    // Overloading operators:
    // read/write
    V& operator()(long long index1, long long index2) {
        return data[index1][index2];
    }

    // fucntion to add two matrixes
    Matrix operator+(Matrix v) const {
        if (NR != v.size_rows() || NC != v.size_columns()) {
            throw std::invalid_argument("received negative value");
        }

        Matrix<V, NR, NC> result;
        for (int i = 0; i < NR; i++) {
            for (int j = 0; j < NR; j++) {
                result(i,j) = this->data[i][j] + v(i, j);
            }
        }
        return result;
    }


    // fucntion to subtract two matrixes
    Matrix operator-(Matrix v) const {
        if (NR != v.size_rows() || NC != v.size_columns()) {
            throw std::invalid_argument("received negative value");
        }

        Matrix<V, NR, NC> result;
        for (int i = 0; i < NR; i++) {
            for (int j = 0; j < NR; j++) {
                result(i, j) = this->data[i][j] - v(i, j);
            }
        }
        return result;
    }


    // fucntion to subtract a scalar value
    Matrix operator+(double x) const {
        Matrix<V, NR, NC> result;
        for (int i = 0; i < NR; i++) {
            for (int j = 0; j < NR; j++) {
                result(i, j) = this->data[i][j] - x;
            }
        }
        return result;
    }


    // fucntion to premultiply with a scalar value
    Matrix operator*(double x) const {
        Matrix<V, NR, NC> result;
        for (int i = 0; i < NR; i++) {
            for (int j = 0; j < NR; j++) {
                result(i, j) = this->data[i][j] * x;
            }
        }
        return result;
    }

    // Subquestion (d)
    template <typename F>
    friend Matrix operator*(const F& x, Matrix pt) {
        Matrix result;
        for (int i = 0; i < NR; i++) {
            for (int j = 0; j < NR; j++) {
                result(i, j) = pt(i,j) * x;
            }
        }
        return result;
    }

    // Subquestion (e)
    void modify(const std::function <V(V&)> f) {
        for_each(data.begin(), data.end(), [&](std::array<V,NC>& row) -> void {
            for_each(row.begin(), row.end(), f);
            });
    }

    // print utility fucntion
    void print() {
        for (auto& row : data) {
            for (auto& ele : row) {
                std::cout << ele << "\t";
            }
            std::cout << std::endl;
        }
    }

    // size utility functions
    long long size_rows() {
        return data.size();
    }

    long long size_columns() {
        return data[0].size();
    }
};

int main()
{
    // testing Matrix class
    // testing constructors
    // Subquestion (b)
    Matrix<int, 3, 3> matrix1; // default constructor
    Matrix<int, 3, 3> matrix2(10); // constructor with parameter
    Matrix<int, 3, 3> matrix3(matrix2); // copy constructor

    std::cout << "matrix1: " << std::endl;
    matrix1.print();

    std::cout << "\nmatrix2: " << std::endl;
    matrix2.print();

    std::cout << "\nmatrix3: " << std::endl;
    matrix3.print();

    // Subquestion (c)
    std::cout << "\n\nreading/writing from/to the matrix3\n";
    // reading matrix3 using operator()
    std::cout << "\nvec3[2]: " << matrix3(2,2) << std::endl;

    // modifying the matrix3 using the operator()
    matrix3(2, 2) = 141;
    std::cout << "\nvec3[2] after modifying: " << matrix3(2, 2) << std::endl;

    // adding and subtracting two matrices
    Matrix<int, 3, 3> matrix4(15); 
    auto result_add = matrix2 + matrix4;
    std::cout << "\naddition of two matrices: \n";
    result_add.print();

    auto result_sub = matrix2 - matrix4;
    std::cout << "\nsubtraction of two matrices: \n";
    result_sub.print();

    auto result_unary_sub = matrix2 - 5;
    std::cout << "\nunary subtraction on matrices: \n";
    result_unary_sub.print();

    auto result_premult_scalar = matrix2 * 10;
    std::cout << "\npremultiply matrice: \n";
    result_premult_scalar.print();

    // Subquestion (d)
    auto result_template_scalar_mult = 20 * matrix2;
    std::cout << "\ntemplate member funtion to multiply scalar and matrix: \n";
    result_template_scalar_mult.print();

    // Subquestion (e)
    // scaling each element by 2
    auto test_fucntion = [](int& x) -> int { x = x * 2;
    return x;};

    matrix2.modify(test_fucntion);
    std::cout << "\nModifying each element of the matrix2\n";
    matrix2.print();

    
    return 0;
}
