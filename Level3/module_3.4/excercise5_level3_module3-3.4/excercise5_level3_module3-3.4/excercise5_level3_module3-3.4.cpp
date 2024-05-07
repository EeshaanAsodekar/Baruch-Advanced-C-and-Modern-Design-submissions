#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <future>
#include <random>
#include <ppl.h>
#include <omp.h>

void fill_vec_rand_value(std::vector<int>& vec) {
    std::default_random_engine dre;
    std::uniform_int_distribution<int> distribution(1, 100);

    for (int i = 0;i < vec.size();i++) {
        vec[i] = distribution(dre);
    }
}


// Function to calculate sum of vector elements
void sum_elements_t(std::vector<int>::iterator begin, std::vector<int>::iterator end, double& result) {
    result = std::accumulate(begin, end, 0.0);
}

// Function to create threads for parallel processing
void sum_parallel_t(std::vector<int>::iterator begin, std::vector<int>::iterator end, double& result) {
    auto size = std::distance(begin, end);
    // if length lesser than 1000, directly use accumulate
    if (size < 1000) {
        sum_elements_t(begin, end, result);
    }
    else {
        // if not, we break into two sections
        auto mid = begin + size / 2;

        // right half
        double secondHalfResult = 0;
        std::thread t1(sum_parallel_t, mid, end, std::ref(secondHalfResult));

        // left half
        double firstHalfResult = 0;
        sum_parallel_t(begin, mid, firstHalfResult);

        // wait for the second half to finish
        t1.join();

        // finally summing them up
        result = firstHalfResult + secondHalfResult;
    }
}




// function to calculate sum of vector elements
double sum_elements(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    return std::accumulate(begin, end, 0.0);
}

// function to create future for parallel processing (using tasks)
double sum_parallel(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    auto size = std::distance(begin, end);
    // if length lesser than 1000, directly use accumulate
    if (size < 1000) {
        return sum_elements(begin, end);
    }
    else {
        // if not, we break into two sections
        auto mid = begin + size / 2;

        // right half
        auto handle = std::async(std::launch::async, sum_parallel, mid, end);

        // left half
        double secondHalfResult = sum_parallel(begin, mid);

        // finally summing them up
        return handle.get() + secondHalfResult;
    }
}

// Subquestion (f)
// function to calculate product of vector elements
void product_elements(std::vector<int>::iterator begin, std::vector<int>::iterator end, int& result) {
    result = std::accumulate(begin, end, 1, std::multiplies<int>());
}


int main() {
    // create a huge numeric array
    std::vector<int> vec(1'000'000);

    fill_vec_rand_value(vec);

    // Subquestion (a)
    // measure processing time for std::accumulate
    auto start = std::chrono::high_resolution_clock::now();
    auto sum_sequential = std::accumulate(vec.begin(), vec.end(), 0);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by std::accumulate: " << duration.count() << " microseconds" << std::endl;

    // Subquestion (b)
    // measure processing time for parallel processing
    start = std::chrono::high_resolution_clock::now();
    auto parallelSum = sum_parallel(vec.begin(), vec.end());
    stop = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\nTime taken by parallel processing (task based): " << duration2.count() << " microseconds" << std::endl;

    std::cout << "percentage change in speed using parallel (task based): " << 100*(double)(duration2.count() - duration.count()) / (double)duration.count();

    // Subquestion (c)
    // OpenMP code
    omp_set_num_threads(2);
    double sumParallel_omp = 0.0;

    start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for reduction (+:sumParallel_omp)
    for (long i = 0; i < vec.size(); ++i)
    {
        sumParallel_omp += vec[i];
    }
    stop = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "\n\nTime taken by parallel processing (omp based): " << duration3.count() << " microseconds" << std::endl;
    std::cout << "percentage change speed using parallel(omp based): " << 100 * (double)(duration3.count() - duration.count()) / (double)duration.count();

    /*
    * NOTE: Run times vary during each run
    * Time taken by std::accumulate: 4937 microseconds
    * Time taken by parallel processing: 537215 microseconds
    * percentage change in speed using parallel: 10781.4
    * Time taken by parallel processing omp: 3672 microseconds
    * percentage change speed using parallel(omp): -25.6228
    */

    // Subquestion (e)
    // measure processing time for parallel processing using thread
    start = std::chrono::high_resolution_clock::now();
    double sum_parallel_result = 0;
    sum_parallel_t(vec.begin(), vec.end(), sum_parallel_result);
    stop = std::chrono::high_resolution_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\n\nTime taken by parallel processing (thread based): " << duration4.count() << " microseconds" << std::endl;
    std::cout << "percentage change speed using parallel(thread based): " << 100 * (double)(duration4.count() - duration.count()) / (double)duration.count();

    // Subquestion(f)
    start = std::chrono::high_resolution_clock::now();
    int prod_result = 1;
    product_elements(vec.begin(), vec.end(), prod_result);
    stop = std::chrono::high_resolution_clock::now();
    auto duration5 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\n\nTime taken by product accumulator: " << duration5.count() << " microseconds" << std::endl;

    
    // Subquestion (g)
    for (int N = 1'000'000; N <= 5'000'000; N += 1'000'000) {
        std::vector<int> v(N);
        fill_vec_rand_value(v);

        // Sequential transform
        auto start = std::chrono::high_resolution_clock::now();
        std::transform(v.begin(), v.end(), v.begin(), [](int n) { return n * n; });
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Sequential transform for N = " << N << ": " << duration.count() << " microseconds\n";

        // Parallel transform
        start = std::chrono::high_resolution_clock::now();
        Concurrency::parallel_transform(v.begin(), v.end(), v.begin(), [](int n) { return n * n; });
        stop = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Parallel transform for N = " << N << ": " << duration2.count() << " microseconds\n";

        std::cout << "\nspeedup: " << (double)(duration2.count() - duration.count() )/ (double)duration.count() << std::endl;

        // Sequential sort
        start = std::chrono::high_resolution_clock::now();
        std::sort(v.begin(), v.end());
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Sequential sort for N = " << N << ": " << duration.count() << " microseconds\n";

        // Parallel sort
        start = std::chrono::high_resolution_clock::now();
        Concurrency::parallel_sort(v.begin(), v.end());
        stop = std::chrono::high_resolution_clock::now();
        duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Parallel sort for N = " << N << ": " << duration2.count() << " microseconds\n";

        std::cout << "\nspeedup: " << (double)(duration2.count() - duration.count()) / (double)duration.count() << std::endl;
    }

    /*
    * as we go on increasing the number of elements in the vector
    * we can see that the speed up factor increases (not always, but the general trend is in that direction).
    * 
    * But, we need to increase the vector size even more to be able to clearly see the trend
    * My personal machine had limitations.
    */

    /* for one run:
 Time taken by std::accumulate: 2618 microseconds

Time taken by parallel processing (task based): 416502 microseconds
percentage change in speed using parallel (task based): 15809.2

Time taken by parallel processing (omp based): 5497 microseconds
percentage change speed using parallel(omp based): 109.969

Time taken by parallel processing (thread based): 2115513 microseconds
percentage change speed using parallel(thread based): 80706.5

Time taken by product accumulator: 2119 microseconds
Sequential transform for N = 1000000: 1928 microseconds
Parallel transform for N = 1000000: 1564433 microseconds

speedup: 810.428
Sequential sort for N = 1000000: 99257 microseconds
Parallel sort for N = 1000000: 7927922 microseconds

speedup: 78.8727
Sequential transform for N = 2000000: 4004 microseconds
Parallel transform for N = 2000000: 3304178 microseconds

speedup: 824.219
Sequential sort for N = 2000000: 208430 microseconds
Parallel sort for N = 2000000: 19618138 microseconds

speedup: 93.1234
Sequential transform for N = 3000000: 14774 microseconds
Parallel transform for N = 3000000: 6404338 microseconds

speedup: 432.487
Sequential sort for N = 3000000: 727470 microseconds
Parallel sort for N = 3000000: 30108505 microseconds

speedup: 40.388
Sequential transform for N = 4000000: 9068 microseconds
Parallel transform for N = 4000000: 7221206 microseconds

speedup: 795.339
Sequential sort for N = 4000000: 465376 microseconds
Parallel sort for N = 4000000: 32725684 microseconds

speedup: 69.321
Sequential transform for N = 5000000: 17351 microseconds
Parallel transform for N = 5000000: 10186160 microseconds

speedup: 586.065
Sequential sort for N = 5000000: 858700 microseconds
Parallel sort for N = 5000000: 52542046 microseconds

speedup: 60.1879

    */

    return 0;
}
