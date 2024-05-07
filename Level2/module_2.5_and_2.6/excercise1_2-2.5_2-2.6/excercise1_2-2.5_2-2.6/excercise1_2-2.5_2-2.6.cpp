#include <iostream>
#include <cmath>
#include <limits>

// given function
template <typename T>
const char* Classify(T t)
{
    switch (std::fpclassify(t))
    {
    case FP_INFINITE:  return "Inf";
    case FP_NAN: return "NaN";
    case FP_NORMAL:    return "normal";
    case FP_SUBNORMAL: return "subnormal";
    case FP_ZERO: return "zero";
    default:  return "unknown";
    }
}

template <typename T>
void evaluate(T input_expression)
{
    std::cout << "Expression checking:\n";
    std::cout << "is a nan " << std::boolalpha << isnan(input_expression) << std::endl;
    std::cout << "is infinite " << std::boolalpha << isinf(input_expression) << std::endl;
    std::cout << "is finite " << std::boolalpha << isfinite(input_expression) << std::endl;
    std::cout << "is normal " << std::boolalpha << isnormal(input_expression) << std::endl;
}


int main()
{
    // Subquestion (a)
    constexpr double val = std::numeric_limits<double>::max();
    std::cout << Classify<double>(val) << std::endl; // normal
    std::cout << Classify<double>(2.0 * val) << std::endl; // infinity
    std::cout << Classify<double>(3.1415 + val) << std::endl;// normal
    
    constexpr double val2 = std::numeric_limits<double>::lowest() - 3.1415;
    std::cout << Classify<double>(val2) << std::endl; // normal
    std::cout << Classify<double>(val2 / 2.0) << std::endl; // normal
    std::cout << Classify<double>(DBL_MIN / 2) << std::endl; // subnormal

    // Subqestion (b)
    double factor = 2.0;
    auto val3 = factor * std::numeric_limits<double>::max();
    std::cout << "\nfor val3:\n";
    evaluate(val3); // infinite
    std::cout << "\nfor val3 - val3:\n";
    evaluate(val3 - val3);// NaN
    std::cout << "\nfor std::sqrt(-1.0):\n";
    evaluate(std::sqrt(-1.0));// NaN
    std::cout << "\nfor std::log(0.0):\n";
    evaluate(std::log(0.0));// infinite
    std::cout << "\nfor std::exp(val3):\n";
    evaluate(std::exp(val3));// infinite

    return 0;
}
