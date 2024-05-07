#include <chrono>
#include <algorithm>

class StopWatch
{
public:
    StopWatch() : start_time(std::chrono::high_resolution_clock::now()), end_time(start_time) {}

    void StartStopWatch() { // starting the stop watch ; setting start_time variable
        start_time = std::chrono::high_resolution_clock::now();
    }

    void StopStopWatch() { // pausing the stop watch ; setting the end_time variable
        end_time = std::chrono::high_resolution_clock::now();
    }

    void Reset() { // to re-initialize the stop watch to default
        start_time = std::chrono::high_resolution_clock::now();
        end_time = start_time;
    }

    double GetTime() const { // to return the duration (in seconds) that was timed using the stop watch
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return duration.count() / 1000000.0;
    }

private:
    StopWatch(const StopWatch&); // to prevent copying of objects
    StopWatch& operator=(const StopWatch&); // to prevent copying of objects

    // variables to hold the start and end time stop watch
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
};

#include <iostream>
#include <thread>
#include <vector>

int main() {
    StopWatch sw;

    // Operation 1: Sleeping for 1 second
    sw.StartStopWatch();
    std::this_thread::sleep_for(std::chrono::seconds(1));  // simulate a task
    sw.StopStopWatch();
    std::cout << "Elapsed time for sleep: " << sw.GetTime() << " seconds\n"; 
    sw.Reset();

    // Operation 2: Sorting a large vector
    std::vector<int> v(1000000);
    std::generate(v.begin(), v.end(), std::rand);  // Fill with random numbers

    sw.StartStopWatch();
    std::sort(v.begin(), v.end());
    sw.StopStopWatch();
    std::cout << "Elapsed time for sorting: " << sw.GetTime() << " seconds\n";
    sw.Reset();

    // Operation 3: Doing some computations
    double result = 0.0;
    sw.StartStopWatch();
    for (int i = 0; i < 10000000; ++i) {
        result += std::sqrt(i);
    }
    sw.StopStopWatch();
    std::cout << "Elapsed time for computations: " << sw.GetTime() << " seconds\n";
    sw.Reset();
    
    // Operation 4: Adding two large vectors
    std::vector<int> vec1(100000000);
    std::generate(vec1.begin(), vec1.end(), std::rand);

    std::vector<int> vec2(100000000);
    std::generate(vec2.begin(), vec2.end(), std::rand);

    std::vector<int> result_vec(vec1.size());

    sw.StartStopWatch();
    std::transform(vec1.begin(), vec1.end(), vec2.begin(), result_vec.begin(), std::plus<int>());
    sw.StopStopWatch();
    std::cout << "Elapsed time for adding two vectors of length 10'0000'000 via std::transform : " << sw.GetTime() << " seconds\n";

    // class tested; works as desired


    return 0;
}
