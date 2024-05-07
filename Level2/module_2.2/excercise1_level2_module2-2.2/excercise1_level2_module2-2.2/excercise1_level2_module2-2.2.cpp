#include <iostream>
#include <type_traits>
#include <vector>
#include <array>
#include <complex>
#include <algorithm>

// Subquestion (a)
// when an array/vector is input to the Addition() template fucntion
template <typename T>
T Addition_impl(const T& t1, const T& t2, std::true_type) {
    T addition_output = t1; 

    if (t1.size() != t2.size()) {
        std::cout << "vectors of different sizes given as input!\n";
        return addition_output;
    }

    auto it = addition_output.begin();
    for (const auto& val : t2) {
        *it += val;
        ++it;
    }
    return addition_output;
}

// when an scalar is input to the Addition() template fucntion
template <typename T>
T Addition_impl(const T& t1, const T& t2, std::false_type) {
    return t1 + t2;
}

// overarching Addition() fucntion
template <typename T>
T Addition(const T& t1, const T& t2)
{
    // Vector space addition
    return Addition_impl(t1, t2, std::is_compound<T>());
}

// Subquestion (b)
// when an array/vector is input to the AdditiveInvese() template fucntion
template <typename T>
void AdditiveInverse_impl(T& t1, std::true_type) {
    for (auto itr = t1.begin();itr != t1.end();itr++) {
        (*itr) = - (*itr);
    }
}

// when an scalar is input to the AdditiveInvese() template fucntion
template <typename T>
void AdditiveInverse_impl(T& t1, std::false_type) {
    t1*=-1;
}

// overarching AdditiveInvese() template fucntion
template <typename T>
void AdditiveInverse(T& val)
{
    AdditiveInverse_impl(val, std::is_compound<T>());
}

// Subquestion (c)
// implementation when the 1st argument is not of compound type
// i.e when the second argument is the vector
template <typename T1, typename T2>
T2 Vector_Scalar_Multiply_impl(const T1& t1, const T2& t2, std::false_type) {
    T2 result = t2;

    for (auto itr = result.begin();itr != result.end();itr++) {
        *itr = t1 * (*itr);
    }
    return result;
}

// implementation when the 1st argument is of compound type
// i.e when the first argument is the vector
template <typename T1, typename T2>
T1 Vector_Scalar_Multiply_impl(const T1& t1, const T2& t2, std::true_type) {
    T1 result = t1;
    for (auto itr = result.begin(); itr != result.end();itr++) {
        *itr = t2*(*itr);
    }
    return result;
}
// template fucntion to multiply a vector/array and a scalar
template <typename T1, typename T2>
auto Vector_Scalar_Multiply(const T1& t1, const T2& t2) {
    return Vector_Scalar_Multiply_impl(t1, t2, std::is_compound<T1>());
}

int main()
{
    std::vector<double> vec1{ 1.3,2,3,4.5 };
    std::vector<double> vec2{2,3,6,9};

    std::cout << "\nvec1: " << std::endl;
    for_each(vec1.begin(), vec1.end(), [](double x) -> void {std::cout << x << "\t";});

    std::cout << "\nvec2: " << std::endl;
    for_each(vec2.begin(), vec2.end(), [](double x) -> void {std::cout << x << "\t";});

    const int n = 3;
    std::array<double, n> arr1{ 3.5,6.5,7.8 };
    std::array<double, n> arr2{ 6.5,8.5,17.8 };

    double x = 10.5;
    double y = 9.75;

    // testing the functions on double and std::vector

    std::cout << "\n\nAddition(x, y) output: " << Addition(x, y) << std::endl;
    
    std::cout << "\nAddition(vec1, vec2) output: "<< std::endl;
    auto vec_addition_result = Addition(vec1, vec2);
    for_each(vec_addition_result.begin(), vec_addition_result.end(), [](double x) -> void {std::cout << x << "\t";});

    std::cout << "\n\nAdditiveInverse(x) output: ";
    AdditiveInverse(x);
    std::cout << x << std::endl;

    std::cout << "\nAdditiveInverse(vec1) output: " << std::endl;
    AdditiveInverse(vec1);
    for_each(vec1.begin(), vec1.end(), [](double x) -> void {std::cout << x << "\t";});

    std::cout << "\nVector_Scalar_Multiply(vec1,x) output: " << std::endl;
    auto result = Vector_Scalar_Multiply(vec1,x);
    for_each(result.begin(), result.end(), [](double x) -> void {std::cout << x << "\t";});

    // testing the functions on std::array 
    std::cout << "\n\n";

    std::cout << "\narr1: " << std::endl;
    for_each(arr1.begin(), arr1.end(), [](double x) -> void {std::cout << x << "\t";});

    std::cout << "\narr2: " << std::endl;
    for_each(arr2.begin(), arr2.end(), [](double x) -> void {std::cout << x << "\t";});


    std::cout << "\nAddition(arr1, arr2); output: " << std::endl;
    auto arr_addition_result = Addition(arr1, arr2);
    for_each(arr_addition_result.begin(), arr_addition_result.end(), [](double x) -> void {std::cout << x << "\t";});

    std::cout << "\nAdditiveInverse(arr1) output: " << std::endl;
    AdditiveInverse(arr1);
    for_each(arr1.begin(), arr1.end(), [](double x) -> void {std::cout << x << "\t";});

    std::cout << "\nVector_Scalar_Multiply(arr1, x) output: " << std::endl;
    auto result2 = Vector_Scalar_Multiply(arr1, x);
    for_each(result2.begin(), result2.end(), [](double x) -> void {std::cout << x << "\t";});

    // testing the fucntions on std::vector<std::complex<double>>

    std::vector<std::complex<double>> vec1_cmpx{ {1.3, 2.0}, {2.0, 3.0}, {3.0, 4.0}, {4.5, 5.0} };
    std::vector<std::complex<double>> vec2_cmpx{ {2.0, 3.0}, {3.0, 4.0}, {6.0, 7.0}, {9.0, 10.0} };

    std::cout << "\n\n\nvec1_cmpx: " << std::endl;
    for_each(vec1_cmpx.begin(), vec1_cmpx.end(), [](std::complex<double> x) -> void {std::cout << x << "\t";});

    std::cout << "\nvec2_cmpx: " << std::endl;
    for_each(vec2_cmpx.begin(), vec2_cmpx.end(), [](std::complex<double> x) -> void {std::cout << x << "\t";});

    std::cout << "\nAddition(vec1_cmpx, vec1_cmpx) output: " << std::endl;
    auto vec_cmpx_addition_result = Addition(vec1_cmpx, vec2_cmpx);
    for_each(vec_cmpx_addition_result.begin(), vec_cmpx_addition_result.end(),[](std::complex<double> x) -> void { std::cout << x << "\t"; });

    std::cout << "\nadditiveinverse(vec1_cmpx) output: " << std::endl;
    AdditiveInverse(vec1_cmpx);
    for_each(vec1_cmpx.begin(), vec1_cmpx.end(), [](std::complex<double> x) -> void {std::cout << x << "\t";});

    std::cout << "\nVector_Scalar_Multiply(vec1_cmpx,x) output: " << std::endl;
    auto res = Vector_Scalar_Multiply(vec1_cmpx,x);
    for_each(res.begin(), res.end(), [](std::complex<double> x) -> void {std::cout << x << "\t";});

	return 0;
}


