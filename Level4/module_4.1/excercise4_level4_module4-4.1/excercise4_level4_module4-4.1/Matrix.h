#pragma once
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
                result(i, j) = this->data[i][j] + v(i, j);
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
                result(i, j) = pt(i, j) * x;
            }
        }
        return result;
    }

    // Subquestion (e)
    void modify(const std::function <V(V&)> f) {
        for_each(data.begin(), data.end(), [&](std::array<V, NC>& row) -> void {
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
