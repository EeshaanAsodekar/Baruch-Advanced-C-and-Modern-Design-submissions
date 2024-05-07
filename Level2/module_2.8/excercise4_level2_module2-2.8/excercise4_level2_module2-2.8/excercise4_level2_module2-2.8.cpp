#include <iostream>
#include <vector>
#include <algorithm>

// Subquestion (b)
std::vector<bool> intersect(const std::vector<bool>& v1, const std::vector<bool>& v2) {
    if (v1.size() != v2.size()) {
        throw std::invalid_argument("Vectors must be of the same size");
    }

    std::vector<bool> result(v1.size());
    for (std::size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] && v2[i];
    }

    return result;
}

int main()
{
    // Subquestion (b)
    std::vector<bool> vec1, vec2;

    vec1.push_back(1);vec1.push_back(1);vec1.push_back(0);vec1.push_back(1);
    vec2.push_back(0);vec2.push_back(1);vec2.push_back(0);vec2.push_back(1);

    for_each(vec1.begin(), vec1.end(), [](const double& x)->void {std::cout << x << " ";});
    std::cout << "\n";
    for_each(vec2.begin(), vec2.end(), [](const double& x)->void {std::cout << x << " ";});
    std::cout << "\n";

    auto intersection = intersect(vec1, vec2);
    for_each(intersection.begin(), intersection.end(), [](const double& x)->void {std::cout << x << " ";});

    /*
    * we can clearly see that a simple bitwise AND operation which is just using the '&' operator on the std bitset
    * and the boost dynamic bitset, is a whole fucntion, or atlease more verbose code. Therefore the broader
    * bit operation functionality available for bitset and dynamic bitset make it a better choice than vector<bool>.
    * 
    */

    return 0;
}

/* Subquestion (a)
* 
* Where std::vector<bool> lacks compared to stl bitset and boost dynamic bitset:
* 1) std::bitset and boost::dynamic_bitset support bitwise operations directly, while std::vector<bool> does not.
* 2) std::vector<bool> does not meet the requirements of a standard container, which can lead to unexpected behavior
* 3) boost::dynamic_bitset provides additional functionality such as finding the first or next set bit, 
*    which std::vector<bool> does not support
*/