#include <iostream>
#include <algorithm>
#include <vector>


// Subquestion (c)
std::vector<std::vector<int>> powerSet(const std::vector<int>& S) {
    std::vector<std::vector<int>> result = { {} };
    for (int num : S) {
        std::vector<std::vector<int>> newSubsets;
        for (const auto& existingSubset : result) {
            newSubsets.push_back(existingSubset);
            newSubsets.back().push_back(num);
        }
        result.insert(result.end(), newSubsets.begin(), newSubsets.end());
    }
    return result;
}

int main()
{
    auto printVector = [](const std::vector<int> & v){
        for (const auto& element : v) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    };

    std::vector<int> v{ 1,-1,7,8,9,10 };

    std::cout << "vector v:\n";
    printVector(v);
    
    // Subquestion (a)
    std::vector<int> v_reversed;
    std::copy(v.rbegin(), v.rend(), std::back_inserter(v_reversed));
    std::cout << "vector v_reversed:\n";
    printVector(v_reversed);

    // Subquestion (b)
    std::rotate(v.begin(), std::find(v.begin(), v.end(), 8), v.end());
    std::cout << "vector v after rotation:\n";
    printVector(v);

    // Compute the power set of S
    std::vector<std::vector<int>> power_set = powerSet(v);

    // Print the power set
    std::cout << "Power set of v:\n";
    for (const auto& subset : power_set) {
        std::cout << "{ ";
        for (int num : subset) {
            std::cout << num << " ";
        }
        std::cout << "}\n";
    }

    // d) Move the subset {8,9,10} to the front of the container.
    std::vector<int> targetSubset = { 8, 9, 10 };
    auto it = std::find(power_set.begin(), power_set.end(), targetSubset);
    if (it != power_set.end()) {
        std::rotate(power_set.begin(), it, it + 1);
    }

    // Print the power set
    std::cout << "Power set of v:\n";
    for (const auto& subset : power_set) {
        std::cout << "{ ";
        for (int num : subset) {
            std::cout << num << " ";
        }
        std::cout << "}\n";
    }


    return 0;
}