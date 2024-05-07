#include <boost/signals2.hpp>
#include <iostream>
#include <functional>

// Subquestion (b)
// the custom combiner that sums the outputs of the slots
template<typename T>
struct SumCombiner {
    typedef T result_type;

    template <typename InputIterator>
    result_type operator()(InputIterator first, InputIterator last) const {
        result_type sum = T();
        for (; first != last; ++first) {
            sum += *first;
        }
        return sum;
    }
};

// Subquestion (a)
// defining a few slots
double addNumbers(double x, double y) {
    return x + y;
}

double multiplyNumbers(double x, double y) {
    return x * y;
}

double subtractNumbers(double x, double y) {
    return x - y;
}

int main() {
    // creating a signal with the custom combiner
    boost::signals2::signal<double(double, double), SumCombiner<double>> sig;

    // connecting slots to the signal
    sig.connect(&addNumbers);
    sig.connect(&multiplyNumbers);
    sig.connect(&subtractNumbers);

    // Subquestion (c)
    // emit the signal with parameters
    double x = 5.0, y = 3.0;
    double result = sig(x, y);
    // expected = (5+3) + (5*3) + (5-3) = 8 + 15 + 2 = 25
    // matches with output!
    std::cout << "The combined result of adding, multiplying, and subtracting "
        << x << " and " << y << " is: " << result << std::endl;

    return 0;
}
