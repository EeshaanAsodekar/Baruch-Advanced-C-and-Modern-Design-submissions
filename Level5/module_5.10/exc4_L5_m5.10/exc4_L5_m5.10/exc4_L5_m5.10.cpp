#include <boost/numeric/ublas/vector.hpp>
#include <iostream>
#include <algorithm>
#include <tuple>

using namespace boost::numeric::ublas;
using Range = std::tuple<std::size_t, std::size_t>;
using Result = std::tuple<Range, bool>;

// Subquestion (a)
// function to find sequential values where the first is <= x and the next is > x
Result find_sequential_greater(const vector<double>& v, double x) {
    // incorrect vector
    if (v.size() < 2) return { Range(999, 999), false };

    for (std::size_t j = 0; j < v.size() - 1; ++j) {
        if (v[j] <= x && v[j + 1] > x) {
            return { Range(j, j + 1), true };
        }
    }
    return { Range(999, 999), false }; // if nothing found
}

// Subquestion (a)
// wrapper to find the index of a value using std::find
std::size_t find_index(const vector<double>& v, double value) {
    auto it = std::find(v.begin(), v.end(), value);
    return it != v.end() ? std::distance(v.begin(), it) : -1;
}

// Subquestion (b)
// wrapper for std::lower_bound and std::upper_bound
Result find_bounds(const vector<double>& v, double x) {
    auto lower = std::lower_bound(v.begin(), v.end(), x);
    auto upper = std::upper_bound(v.begin(), v.end(), x);

    if (lower != v.end()) {
        std::size_t lower_index = std::distance(v.begin(), lower);
        std::size_t upper_index = std::distance(v.begin(), upper);
        return { Range(lower_index, upper_index), true };
    }
    return { Range(999, 999), false };
}

// Subquestion (c)
// wrapper for std::equal_range
Result find_equal_range(const vector<double>& v, double x) {
    auto bounds = std::equal_range(v.begin(), v.end(), x);
    if (bounds.first != bounds.second) {
        return { Range(std::distance(v.begin(), bounds.first), std::distance(v.begin(), bounds.second)), true };
    }
    return { Range(999, 999), false };
}

// Subquestion (d)
// testing std::find_if_not
void test_find_if_not() {
    vector<double> v(5);
    for (int i = 0; i < v.size(); ++i) v(i) = i * 2; // filling with even numbers

    // finding the first odd number (which shouldn't exist)
    auto it = std::find_if_not(v.begin(), v.end(), [](double n) { return int(n) % 2 == 0; });
    std::cout << "Test find_if_not: ";
    if (it != v.end()) {
        std::cout << "Found an odd number at index " << std::distance(v.begin(), it) << ": " << *it << std::endl;
    }
    else {
        std::cout << "No odd numbers found." << std::endl;
    }
}

int main() {
    vector<double> v(10);
    for (int i = 0; i < v.size(); ++i) v(i) = i; 

    auto result = find_sequential_greater(v, 5.5);
    std::cout << "Result of find_sequential_greater: (" << std::get<0>(std::get<0>(result)) << ", " << std::get<1>(std::get<0>(result)) << "), " << std::get<1>(result) << std::endl;

    auto bounds_result = find_bounds(v, 5.5);
    std::cout << "Result of find_bounds: (" << std::get<0>(std::get<0>(bounds_result)) << ", " << std::get<1>(std::get<0>(bounds_result)) << "), " << std::get<1>(bounds_result) << std::endl;

    auto equal_range_result = find_equal_range(v, 5);
    std::cout << "Result of find_equal_range: (" << std::get<0>(std::get<0>(equal_range_result)) << ", " << std::get<1>(std::get<0>(equal_range_result)) << "), " << std::get<1>(equal_range_result) << std::endl;

    test_find_if_not();

    return 0;
}