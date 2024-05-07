#include <iostream>
#include <array>
#include <algorithm>
#include <functional>

template<typename T, int N> class Vector {
private:
    // Subquestion (a)
    std::array<T, N> data;
    // choosing to use the std::array as the data structure ADT to hold the data
    // rationale: (1) can use a lot of the internal functionality of the std::array
    // (2) although it might not be as efficient as an light weight array (T arr[]),
    // and might have a greater overhead; but the functionality makes up for it.

public: 
    // default constructor
    Vector() : data{} {}

    // constructor with single numerical value as argument
    Vector(T val) : data{} {
        data.fill(val);
    }

    // copy constructor
    Vector(const Vector & vec): data(vec.data){}

    // read/write 
    T& operator[](long long int index) {
        return data[index];
    }

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


    Vector operator*(double factor) const {
        Vector result;
        for (int i = 0; i < N; ++i) {
            result.data[i] = factor * this->data[i];
        }
        return result;
    }

    // Subquestion (d)
    template <typename F>
    friend Vector operator*(const F& a, const Vector& pt) {
        Vector result;
        for (int i = 0; i < N; ++i) {
            result.data[i] = a * pt.data[i];
        }
        return result;
    }

    // Subquestion (e)
    void modify(const std::function <T(T&)>& f) {
        for_each(data.begin(), data.end(), f);
    }

    // print utility fucntion
    void print() const {
        for (auto ele : data) {
            std::cout << ele << "\t";
        }
        std::cout << "\n";
    }

    // utility funtion to return the size of a vector:
    long long int size() {
        return N;
    }
};
template <typename T, int NR, int NC> class Matrix;

int main()
{
    // Subquestion (b)
    Vector<int, 5> vec1; // default constructor
    Vector<int, 5> vec2(10); // constructor with parameters
    Vector<int, 5> vec3(vec2); // copy constructor

    std::cout << "\nvec1:\n";
    vec1.print();
    std::cout << "\nvec2:\n";
    vec2.print();
    std::cout << "\nvec3:\n";
    vec3.print();

    // Subquestion (c)
    std::cout << "\n\nreading/writing from/to the vec3\n";

    std::cout << "\nvec3[2]: " << vec3[2] << std::endl;

    // modifying the vec3 using the operator[]
    vec3[2] = 141;
    std::cout << "\nvec3[2] after modifying: " << vec3[2] << std::endl;

    // adding and subtracting two vectors; and unary minus
    Vector<int, 5> vec4(3);
    auto addition_result = vec2 + vec4;
    std::cout << "\nadding two vectors: \n";
    addition_result.print();

    auto subtraction_result = vec2 - vec4;
    std::cout << "\nsubtraction two vectors: \n";
    subtraction_result.print();

    auto unary_subtraction_result = vec2 - 8;
    std::cout << "\nunary subtraction: \n";
    unary_subtraction_result.print();

    // Premultiplication by a scalar;
    auto premult_result = vec2 * 10;
    std::cout << "\npremultiplication by a scalar: \n";
    premult_result.print();

    // Subquestion (d)
    Vector<int, 5> vec5(15);
    auto result_scalar_mult = 10 * vec5;
    std::cout << "\ntemplate member function to multiply vector and scalar: \n";
    result_scalar_mult.print();

    // Subquestion (e)
    // scaling each element by 2
    auto test_fucntion = [](int& x) -> int { x = x * 2; 
    return x;};

    vec5.modify(test_fucntion);
    std::cout << "\nModifying each element of the vec5\n";
    vec5.print();

    return 0;
}