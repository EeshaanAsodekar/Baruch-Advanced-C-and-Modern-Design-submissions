#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <string>
#include <boost/numeric/ublas/vector.hpp>

template <typename T, template <typename S, typename Alloc> class Container, typename TAlloc>
using Range = std::tuple<std::size_t, std::size_t>;

template <typename T, template <typename S, typename Alloc> class Container, typename TAlloc>
using Result = std::tuple<Range<T, Container, TAlloc>, bool>;

template <typename T, template <typename S, typename Alloc> class Container, typename TAlloc>
Result<T, Container, TAlloc> find_sequential_greater(const Container<T, TAlloc>& v, const T& x) {
    if (v.size() < 2) return { Range<T, Container, TAlloc>(999, 999), false };

    for (std::size_t j = 0; j < v.size() - 1; ++j) {
        if (v[j] <= x && v[j + 1] > x) {    
            return { Range<T, Container, TAlloc>(j, j + 1), true };
        }
    }
    return { Range<T, Container, TAlloc>(999, 999), false };
}

template <typename T, template <typename S, typename Alloc> class Container, typename TAlloc>
Result<T, Container, TAlloc> find_bounds(const Container<T, TAlloc>& v, const T& x) {
    auto lower = std::lower_bound(v.begin(), v.end(), x);
    auto upper = std::upper_bound(v.begin(), v.end(), x);

    if (lower != v.end()) {
        return { Range<T, Container, TAlloc>(std::distance(v.begin(), lower), std::distance(v.begin(), upper)), true };
    }
    return { Range<T, Container, TAlloc>(999, 999), false };
}

template <typename T, template <typename S, typename Alloc> class Container, typename TAlloc>
Result<T, Container, TAlloc> find_equal_range(const Container<T, TAlloc>& v, const T& x) {
    auto bounds = std::equal_range(v.begin(), v.end(), x);

    if (bounds.first != bounds.second) {
        return { Range<T, Container, TAlloc>(std::distance(v.begin(), bounds.first), std::distance(v.begin(), bounds.second)), true };
    }
    return { Range<T, Container, TAlloc>(999, 999), false };
}


template <typename T, template <typename S, typename Alloc> class Container, typename TAlloc>
std::size_t find_index(const Container<T, TAlloc>& v, const T& x) {
    auto it = std::find(v.begin(), v.end(), x);
    return it != v.end() ? std::distance(v.begin(), it) : -1;
}

template <typename T, template <typename, typename> class Container, typename Alloc>
void print(const std::string& comment, const Container<T, Alloc>& container) {
    std::cout << comment << ": ";
    std::for_each(container.begin(), container.end(), [](const T& t) { std::cout << t << ", "; });
    std::cout << std::endl;

    for (std::size_t i = 0; i < container.size(); ++i) {
        std::cout << container[i] << ", ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<double> v1{ 2.0, 3.0, 4.0, -6.0 };
    print("STL", v1);

    boost::numeric::ublas::vector<double> v2(4);
    v2[0] = 2.0; v2[1] = 3.0; v2[2] = 4.0; v2[3] = -6.0;
    print("Boost", v2);

    // testing find_sequential_greater
    auto result = find_sequential_greater(v1, 3.0);
    std::cout << "Result of find_sequential_greater in STL: ("
        << std::get<0>(std::get<0>(result)) << ", "
        << std::get<1>(std::get<0>(result)) << "), "
        << std::get<1>(result) << std::endl;

    auto result2 = find_sequential_greater(v2, 3.0);
    std::cout << "Result of find_sequential_greater in Boost: ("
        << std::get<0>(std::get<0>(result2)) << ", "
        << std::get<1>(std::get<0>(result2)) << "), "
        << std::get<1>(result2) << std::endl;

    // testing the other generic fucntions
    std::vector<double> v3{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    boost::numeric::ublas::vector<double> v4(6);
    for (int i = 0; i < 6; ++i) v4[i] = i + 1.0;  // similar data as v3 for comparison

    auto bounds_result = find_bounds(v3, 4.0);
    auto equal_range_result = find_equal_range(v3, 3.0);
    auto index_result = find_index(v3, 2.0);

    std::cout << "Bounds in STL vector: (" << std::get<0>(std::get<0>(bounds_result)) << ", " << std::get<1>(std::get<0>(bounds_result)) << "), " << std::get<1>(bounds_result) << std::endl;
    std::cout << "Equal range in STL vector: (" << std::get<0>(std::get<0>(equal_range_result)) << ", " << std::get<1>(std::get<0>(equal_range_result)) << "), " << std::get<1>(equal_range_result) << std::endl;
    std::cout << "Index of 2.0 in STL vector: " << index_result << std::endl;

    auto bounds_result2 = find_bounds(v4, 4.0);
    auto equal_range_result2 = find_equal_range(v4, 3.0);
    auto index_result2 = find_index(v4, 2.0);

    std::cout << "Bounds in Boost vector: " << std::get<0>(std::get<0>(bounds_result2)) << ", " << std::get<1>(std::get<0>(bounds_result2)) << "), " << std::get<1>(bounds_result2) << std::endl;
    std::cout << "Equal range in Boost vector: " << std::get<0>(std::get<0>(equal_range_result2)) << ", " << std::get<1>(std::get<0>(equal_range_result2)) << "), " << std::get<1>(equal_range_result2) << std::endl;
    std::cout << "Index of 2.0 in Boost vector: " << index_result2 << std::endl;

    return 0;
}