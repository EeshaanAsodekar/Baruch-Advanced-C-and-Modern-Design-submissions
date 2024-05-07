#pragma once
#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric> // for std::inner_product
#include <complex>

// code from Vector class of Excercise 2 4-4.1
// adding the required functionality
template<typename T, int N> class Vector {
private:
    std::array<T, N> data;

public:
    // default constructor
    Vector() : data{} {}

    // constructor with single numerical value as argument
    Vector(T val) : data{} {
        data.fill(val);
    }

    // copy constructor
    Vector(const Vector& vec) : data(vec.data) {}

    // read/write 
    T& operator[](long long int index) {
        return data[index];
    }

    // Subquestion (a): Add iterator functionality to Vector class
    // Add iterator functionality
    typedef typename std::array<T, N>::iterator iterator;
    typedef typename std::array<T, N>::const_iterator const_iterator;

    iterator begin() { return data.begin(); }
    const_iterator cbegin() const { return data.begin(); }
    iterator end() { return data.end(); }
    const_iterator cend() const { return data.end(); }

    // Vector operation fucntions:
    // fucntion to add two vectors
    Vector operator+(Vector v) const {

        if (N != v.size()) {
            throw std::invalid_argument("received negative value");
        }

        Vector result;
        for (int i = 0; i < N; ++i) {
            result.data[i] = this->data[i] + v.data[i];
        }
        return result;
    }

    // fucntion to subtract two vectors
    Vector operator-(Vector v) const {

        if (N != v.size()) {
            throw std::invalid_argument("received negative value");
        }

        Vector result;
        for (int i = 0; i < N; ++i) {
            result.data[i] = this->data[i] - v.data[i];
        }
        return result;
    }

    // fucntion to subtract of a scalar from the vector
    Vector operator-(double x) const {

        Vector result;
        for (int i = 0; i < N; ++i) {
            result.data[i] = this->data[i] - x;
        }
        return result;
    }

    // scalar multiplication
    Vector operator*(double factor) const {
        Vector result;
        for (int i = 0; i < N; ++i) {
            result.data[i] = factor * this->data[i];
        }
        return result;
    }

    template <typename F>
    friend Vector operator*(const F& a, const Vector& pt) {
        Vector result;
        for (int i = 0; i < N; ++i) {
            result.data[i] = a * pt.data[i];
        }
        return result;
    }

    void modify(const std::function <T(T&)>& f) {
        for_each(data.begin(), data.end(), f);
    }

    void print() const {
        std::cout << "\t";
        for (auto ele : data) {
            std::cout << ele << "\t";
        }
        std::cout << "\n";
    }

    long long int size() {
        return N;
    }
};
template <typename T, int N>
using Matrix = Vector<Vector<T, N>, N>;

// Subquestion (a): Create user-friendly wrappers for the STL inner_product functions
// inner_product function without binary operations
template <typename T, int N>
T inner_product(const Vector<T, N>& v1, const Vector<T, N>& v2, T initValue) {
    return std::inner_product(v1.cbegin(), v1.cend(), v2.cbegin(), initValue);
}

template <typename T>
using BinaryFunction = std::function < T(const T& t1, const T& t2)>;

// inner_product function with binary operations
template <typename T, int N>
T inner_product(const Vector<T, N>& v1, const Vector<T, N>& v2, T initValue,
    const BinaryFunction<T>& op1, const BinaryFunction<T>& op2) {
    return std::inner_product(v1.cbegin(), v1.cend(), v2.cbegin(), initValue, op1, op2);
}

// Subquestion (d) write code to compute outer product of two vectors
template <typename T, int N>
Matrix<T, N> outer_product(Vector<T, N>& v1, Vector<T, N>& v2) {
    Matrix<T, N> result;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = v1[i] * v2[j];
        }
    }
    return result;
}

// Subquestion (e) specializing the code for matrix of complex 
template <typename T, int N>
Matrix<std::complex<T>, N> outer_product(const Vector<std::complex<T>, N>& v1, const Vector<std::complex<T>, N>& v2) {
    Matrix<std::complex<T>, N> result;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = v1[i] * std::conj(v2[j]);
        }
    }
    return result;
}

template <typename T, int N>
void printMatrix(Matrix<T, N> & mat) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << mat[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

template <typename T, int N>
void printMatrixC(Matrix<std::complex<T>, N>& mat) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << std::real(mat[i][j]) << " + " << std::imag(mat[i][j]) << "i\t";
        }
        std::cout << std::endl;
    }
}