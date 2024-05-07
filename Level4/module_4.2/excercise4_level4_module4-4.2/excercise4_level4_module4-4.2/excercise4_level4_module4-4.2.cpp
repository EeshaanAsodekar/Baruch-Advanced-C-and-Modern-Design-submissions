#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
#include <numeric>
#include <functional>

// Subquestion (a)
template <typename T>
std::map<int, int> frequencyCounter(const std::vector<T> & vec) {
    std::map<int, int> freq;
    // using std::count to update the frequency map
    for (auto ele : vec) {
        if (freq.find(ele) == freq.end()) {
            freq[ele] = std::count(vec.begin(), vec.end(), ele);
        }
    }

    return freq;
}

// Subquestion (b)
template <typename T>
std::tuple<T, T, T, double> funcminMaxSumAvg(const std::vector<T>& vec) {
    return std::make_tuple(*std::min_element(vec.begin(),vec.end()),
        *std::max_element(vec.begin(), vec.end()),
        std::accumulate(vec.begin(),vec.end(),0),
        (std::accumulate(vec.begin(), vec.end(), 0)+0.0)/vec.size());
}

void mapPrinter(std::map<int, int> mymap) {
    std::cout << "{";
    for (auto ele : mymap) {
        std::cout << "{" << ele.first << "->" << ele.second << "}\t";
    }
    std::cout << "}\n";
}

int main()
{
    // Subquestion (a)
    std::vector<int> vec{ 1,2,3,4,44,5,3,3,6,4,4,3,3 };
    auto freq = frequencyCounter(vec);
    mapPrinter(freq);

    // Subquestion (b)
    auto printStats = [](std::tuple<int, int, int, double> tup) {
        std::cout << "\n" << std::get<0>(tup) << " " <<
            std::get<1>(tup) << " " <<
            std::get<2>(tup) << " " <<
            std::get<3>(tup) << "\n";

        };
    std::cout << "\nmin max sum avg:";
    auto stats = funcminMaxSumAvg(vec);
    printStats(stats);

    // Subquestion (c)
    std::vector<int> S{ 1,2,-3,4,5,5,5,6 };
    // Using std::bind2nd()
    auto it1 = std::find_if(S.begin(), S.end(), std::bind2nd(std::equal_to<int>(), 5));
    if (it1 != S.end()) {
        std::cout << "First occurrence of 5 using bind2nd is at position: " << std::distance(S.begin(), it1) << std::endl;
    }
    else {
        std::cout << "5 not found in S using bind2nd" << std::endl;
    }

    // Using std::bind()
    auto it2 = std::find_if(S.begin(), S.end(), std::bind(std::equal_to<int>(), std::placeholders::_1, 5));
    if (it2 != S.end()) {
        std::cout << "First occurrence of 5 using bind is at position: " << std::distance(S.begin(), it2) << std::endl;
    }
    else {
        std::cout << "5 not found in S using bind" << std::endl;
    }

    // Using lambda expression
    auto it3 = std::find_if(S.begin(), S.end(),[](int i) { return i == 5; });
    if (it3 != S.end()) {
        std::cout << "First occurrence of 5 using lambda is at position: " << std::distance(S.begin(), it3) << std::endl;
    }
    else {
        std::cout << "5 not found in S using lambda" << std::endl;
    }

    // Subquestion (d)
    std::vector<int> S2 = { 1,2,5,5,-3,4,5,5,5,6,3,4,5};
    std::vector<int> subRange = { 3,4,5 };

    // Find the position of the first three consecutive elements having the value 5
    it1 = std::search_n(S2.begin(), S2.end(), 3, 5);
    if (it1 != S2.end()) {
        std::cout << "First three consecutive 5s start at position: " << std::distance(S2.begin(), it1) << std::endl;
    }
    else {
        std::cout << "No three consecutive 5s found in S2" << std::endl;
    }

    // Find the position of the first element of the first subrange matching {3,4,5}
    it2 = std::search(S2.begin(), S2.end(), subRange.begin(), subRange.end());
    if (it2 != S2.end()) {
        std::cout << "First subrange {3,4,5} starts at position: " << std::distance(S2.begin(), it2) << std::endl;
    }
    else {
        std::cout << "Subrange {3,4,5} not found in S2" << std::endl;
    }

    // Find the position of the first element of the last subrange matching {3,4,5}
    it3 = std::find_end(S2.begin(), S2.end(), subRange.begin(), subRange.end());
    if (it3 != S2.end()) {
        std::cout << "Last subrange {3,4,5} starts at position: " << std::distance(S2.begin(), it3) << std::endl;
    }
    else {
        std::cout << "Subrange {3,4,5} not found in S2" << std::endl;
    }

    // Subquestion (e)
    auto it = std::adjacent_find(S2.begin(), S2.end());
    if (it != S2.end()) {
        std::cout << "First element in S2 that is equal to the next element is: " << *it << std::endl;
        std::cout << "It's at position: " << std::distance(S2.begin(), it) << std::endl;
    }
    else {
        std::cout << "No such element found in S2" << std::endl;
    }

    // Subquestion (f)
    std::vector<int> S1 = { 1,2,5 };

    // Sort the vectors because std::includes requires sorted ranges
    std::sort(S2.begin(), S2.end());
    std::sort(S1.begin(), S1.end());

    if (std::includes(S2.begin(), S2.end(), S1.begin(), S1.end())) {
        std::cout << "S1 is a subset of S2" << std::endl;
    }
    else {
        std::cout << "S1 is not a subset of S2" << std::endl;
    }

    return 0;
}
