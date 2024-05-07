#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <iterator>
#include <functional>

// Subquestion (a) 
using Range = std::tuple<std::size_t, std::size_t>;
using Result = std::tuple<Range, bool>;

// needed to slightly modify the given code; converted it to template fucntion
// Vector -> std::vector<T>
// value_type -> T

template <typename T>
Result find_sequential_greater(const std::vector<T> & v, T x)
{
    for (std::size_t j = 0; j < v.size(); ++j)
    {
        if (v[j] <= x && v[j + 1] > x)
        {
            return std::make_tuple(
                std::make_tuple(j, j + 1), true);
        }
    }
    return std::make_tuple(std::make_tuple(999, 999), false);
}

// Subquestion (a)
// implementing the same functionality using std::find_if.
template <typename T>
Result find_sequential_greater_findIf(const std::vector<T>& v, T x)
{
    auto it = std::find_if(v.begin(), v.end() - 1, [&](T val) { return val <= x; });
    while (it != v.end() - 1 && *it <= x)
    {
        if (*(it + 1) > x)
        {
            std::size_t index = std::distance(v.begin(), it);
            return std::make_tuple(std::make_tuple(index, index + 1), true);
        }
        ++it;
    }
    return std::make_tuple(std::make_tuple(999, 999), false);
}

// Subquestion (a)
// wrapper for std::find 
template <typename T>
std::size_t find_index(const std::vector<T>& v, T x)
{
    auto it = std::find(v.begin(), v.end(), x);
    return it != v.end() ? std::distance(v.begin(), it) : -1;
}

// Subquestion (b)
template <typename T>
Result find_sequential_greater_lowerBound(const std::vector<T>& v, T x)
{
    auto lower = std::lower_bound(v.begin(), v.end(), x);
    while (lower != v.end() && lower + 1 != v.end())
    {
        if (*(lower + 1) > x) {
            std::size_t index = std::distance(v.begin(), lower);
            return std::make_tuple(std::make_tuple(index, index + 1), true);
        }
        lower++;
    }
    return std::make_tuple(std::make_tuple(999, 999), false);
}

template <typename T>
Result find_sequential_greater_upperBound(const std::vector<T>& v, T x)
{
    auto upper = std::upper_bound(v.begin(), v.end(), x);
    while (upper != v.end() && upper !=v.begin())
    {
        if (*(upper - 1) <= x) {
            std::size_t index = std::distance(v.begin(), upper - 1);
            return std::make_tuple(std::make_tuple(index, index + 1), true);
        }
        upper--;
    }
    return std::make_tuple(std::make_tuple(999, 999), false);
}

// Subquestion (c)
template <typename T>
Result find_sequential_greater_equalRange(std::vector<T>& v, T x)
{
    std::sort(v.begin(), v.end());
    auto rang = std::equal_range(v.begin(), v.end(), x);
    if (rang.first != v.end()) {
        std::size_t index = std::distance(v.begin(), rang.first);
        return std::make_tuple(std::make_tuple(index+1, std::distance(v.begin(), rang.second)), true);
    }
    return std::make_tuple(std::make_tuple(999, 999), false);
}

// Subquestion (d)
template <typename T>
int custom_find_not_if(std::vector<T>& v, std::function<bool(T)> func)
{
    auto itr = std::find_if_not(v.begin(), v.end(), func);

    if (itr != v.end()) {
        return std::distance(v.begin(), itr);
    }

    return -1;
}


int main()
{
    std::vector<int> vec1 {10,11,13,17,17,27,35};
    auto printVector = [](std::vector<int> vec) -> void {for_each(vec.begin(), vec.end(), [](int x) {std::cout << x << "\t";});};
    std::cout << "vec1:" << std::endl;
    printVector(vec1);

    // Subquestion (a) 
    Result res = find_sequential_greater(vec1, 17);
    Range range = std::get<0>(res);
    bool found = std::get<1>(res);
    std::cout << "\nfind_sequential_greater Range index: (" << std::get<0>(range) << ", " << std::get<1>(range) << "), Found: " << std::boolalpha << found << std::endl;
    
    Result res2 = find_sequential_greater_findIf(vec1, 17);
    Range range2 = std::get<0>(res2);
    bool found2 = std::get<1>(res2);
    std::cout << "\nfind_sequential_greater_findIf Range index : (" << std::get<0>(range2) << ", " << std::get<1>(range2) << "), Found: " << std::boolalpha << found2 << std::endl;

    auto itshere = find_index(vec1, 13);
    std::cout << "\n13 is at index: " << itshere << std::endl;

    // Subquestion (b)
    Result res3 = find_sequential_greater_lowerBound(vec1, 17);
    Range range3 = std::get<0>(res3);
    bool found3 = std::get<1>(res3);
    std::cout << "\nfind_sequential_greater_lowerBound Range index: (" << std::get<0>(range3) << ", " << std::get<1>(range3) << "), Found: " << std::boolalpha << found3 << std::endl;

    Result res4 = find_sequential_greater_upperBound(vec1, 17);
    Range range4 = std::get<0>(res4);
    bool found4 = std::get<1>(res4);
    std::cout << "\nfind_sequential_greater_upperBound Range index: (" << std::get<0>(range4) << ", " << std::get<1>(range4) << "), Found: " << std::boolalpha << found4 << std::endl;

    // Subquestion (c)
    Result res5 = find_sequential_greater_equalRange(vec1, 17);
    Range range5 = std::get<0>(res5);
    bool found5 = std::get<1>(res5);
    std::cout << "\nfind_sequential_greater_equalRange Range index: (" << std::get<0>(range5) << ", " << std::get<1>(range5) << "), Found: " << std::boolalpha << found5 << std::endl;


    // subquestion (d) :  Test the algorithm stud::find_if_not() using an example of your choice.
    std::vector<int> vec2{ 10,12,14,17,19,21,30,40};
    std::cout << "\n\nvec2:" << std::endl;
    printVector(vec2);
    auto it = std::find_if_not(vec2.begin(), vec2.end(), [](int i) {return i % 2==0;});
    std::cout << "\nstd::find_if_not The first odd value is: " << *it << '\n';
    std::cout << "\ncustom_find_not_if The first odd value is at index: " << custom_find_not_if<int>(vec2, [](int i) -> bool{return i % 2 == 0;}) << '\n';


    return 0;
}
