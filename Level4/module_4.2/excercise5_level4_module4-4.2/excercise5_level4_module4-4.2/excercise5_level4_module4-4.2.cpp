#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <cmath>
#include <functional>

// Subquestion (b)
// approach 1
// User-defined function object
struct GreaterThan {
    int threshold;
    GreaterThan(int t) : threshold(t) {}
    bool operator()(int x) const { return std::abs(x) > threshold; }
};

std::set<int> transformVectorToSet1(const std::vector<int>& vec, int threshold) {
    std::set<int> s;
    std::copy_if(vec.begin(), vec.end(), std::inserter(s, s.begin()), GreaterThan(threshold));
    return s;
}

// approach 2
// Predefined STL function object
std::set<int> transformVectorToSet2(const std::vector<int>& vec, int threshold) {
    std::set<int> s;

    auto greater_than_threshold = std::bind(std::greater<int>(), std::placeholders::_1, threshold);
    std::copy_if(vec.begin(), vec.end(), std::inserter(s, s.begin()), [&](int x) { return greater_than_threshold(std::abs(x));});
    return s;
}

// approach 3
// Lambda function
std::set<int> transformVectorToSet3(const std::vector<int>& vec, int threshold) {
    std::set<int> s;
    std::copy_if(vec.begin(), vec.end(), std::inserter(s, s.begin()),
        [&](int x){ return std::abs(x) > threshold; });
    return s;
}

int main()
{
    // Subquestion (a)
    // Comparing the three solutions :

    // User - defined function objects : These are flexible and can be used in many different contexts.
    // They can encapsulate state and can be passed around like any other object.
    // However, they can be verbose to define and use, especially for simple operations.
    // 
    // Predefined STL function objects : These are convenient for common operations and 
    // can make the code more readable and concise.However, they are limited to the operations defined 
    // in the STL and cannot encapsulate state.
    // 
    // Lambda functions : These are very flexible and concise, especially for simple operations.
    // They can encapsulate state through captured variables.However, they can become less readable 
    // for complex operations, and defining a free fucntions becomes more favourable in that condition.

    auto printSet = [](std::set<int> s){
        for(const auto& element : s) {
            std::cout << element << ' ';
        }
        std::cout << '\n';
    };

    // Subquestion (b)
    // testing each of the 3 approaches defined
    std::vector<int> vec{ 1,2,1,4,5,5,-1 };

    auto res_set1 = transformVectorToSet1(vec, 2);
    auto res_set2 = transformVectorToSet2(vec, 2);
    auto res_set3 = transformVectorToSet3(vec, 2);

    std::cout << "res_set1:" << std::endl;
    printSet(res_set1);

    std::cout << "\nres_set2:" << std::endl;
    printSet(res_set2);

    std::cout << "\nres_set3:" << std::endl;
    printSet(res_set3);

    // Subquestion (c)
    // User - defined function object : This solution is clear and easy to understand, 
    // as the function object clearly encapsulates the operation being performed.
    // It is also easy to maintain, as changes to the operation only need to be made in one place.
    // However, it is less efficient than the other solutions, as it requires the creation of a function object.
    // 
    // Predefined STL function object : This solution is concise and efficient, 
    // as it uses a predefined function object.However, it is less readable than the other solutions, 
    // as the use of std::bind and std::greater<int> can be confusing to someone unfamiliar with the syntax.
    // 
    // Lambda function : This solution is the most readable, concise, and efficient.
    // The lambda function clearly expresses the operation being performed, 
    // and it does not require the creation of a function object.However, 
    // it may be less maintainable than the user - defined function object solution, 
    // as changes to the operation need to be made in every place the lambda function is used.

    return 0;
}
