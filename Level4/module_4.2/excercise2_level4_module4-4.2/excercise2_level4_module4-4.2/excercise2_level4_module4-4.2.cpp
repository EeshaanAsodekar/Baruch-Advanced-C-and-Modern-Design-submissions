#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

int main()
{
    std::vector<double> vec{ 1.0, 2.0, 3.0, -4.0, 10.0 }; // Not ordered
    std::cout << "vec:" << std::endl;

    for_each(vec.begin(), vec.end(), [](double x) {std::cout << x << "\t";});
    auto pos = std::is_sorted_until(vec.begin(), vec.end());
    if(pos!=vec.end()) std::cout << "\n\nis_sorted_until; bad value: " << *pos << std::endl;

    // Subquestion (a): applying the other three algorithms to this container while experimenting with various binary predicate arguments.
    // Check if the vector is sorted   
    std::cout << "\nis_sorted(vec8.begin(), vec8.end()); sorted: " << std::boolalpha << std::is_sorted(vec.begin(), vec.end()) << '\n';
    
    // check using adjacent_find
    bool is_found = std::adjacent_find(vec.begin(), vec.end(), std::greater<double>()) != vec.end();
    std::cout << "\nstd::adjacent_find(vec.begin(), vec.end(), std::greater<double>()) != vec.end(): " << std::boolalpha << !is_found << '\n';

    // Check if the vector is partitioned according to a predicate
    std::cout << "\nstd::is_partitioned(vec.begin(), vec.end(),[](double i) { return i < 0; });Is partitioned: " << std::boolalpha << std::is_partitioned(vec.begin(), vec.end(),[](double i) { return i < 0; }) << '\n';

    // Subquestion (b)
    // empirically testing the time effiency of the code in this question
    // let us create a large vector which is sorted from except for some section in the middle
    // running the 4 approaches would allow us to empiricaly see which approach is the most time efficient

    std::vector<int> largeVec;

    for (int i = 0;i < 100000;i++) {
        largeVec.push_back(i);
    }
    for (int i = -1;i >= -10;i--) {
        largeVec.push_back(i);
    }
    for (int i = 100000;i < 200000;i++) {
        largeVec.push_back(i);
    }

    auto start = std::chrono::high_resolution_clock::now();
    
    auto pos2 = std::is_sorted_until(largeVec.begin(), largeVec.end());
    std::cout << "\n\nis_sorted_until; bad value: " << *pos2 << std::endl;
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;


    start = std::chrono::high_resolution_clock::now();

    // Check if the vector is sorted   
    std::cout << "\nis_sorted(vec8.begin(), vec8.end()); sorted: " << std::boolalpha << std::is_sorted(largeVec.begin(), largeVec.end()) << '\n';

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;


    start = std::chrono::high_resolution_clock::now();

    // Check using adjacent_find
    is_found = std::adjacent_find(largeVec.begin(), largeVec.end(), std::greater<double>()) != largeVec.end();
    std::cout << "\nstd::adjacent_find(largeVec.begin(), largeVec.end(), std::greater<double>()) != largeVec.end(): " << std::boolalpha << !is_found << '\n';

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;



    start = std::chrono::high_resolution_clock::now();

    // Check if the vector is partitioned according to a predicate
    std::cout << "\nstd::is_partitioned(vec.begin(), vec.end(),[](double i) { return i < 0; });Is partitioned: " << std::boolalpha << std::is_partitioned(largeVec.begin(), largeVec.end(), [](double i) { return i < 0; }) << '\n';
    
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    // Observations about time efficiency of the various approaches:
    // When dealing with arrays of smaller size, both "is_sorted" and 
    // "adjacent_find" outperform "is_sorted_until". This is because "is_sorted" doesn't 
    // have to keep track of the location where the sorting order is broken. 
    // However, for larger arrays, "adjacent_find" proves to be the quickest. 
    // Interestingly, "is_sorted" lags behind "is_sorted_until" in this scenario. 
    // This could be due to the fact that both "adjacent_find" and "is_sorted_until" 
    // halt as soon as they encounter a violation, whereas "is_sorted" continues to process the entire vector.

    return 0;
}
