#pragma once
#include <chrono>

// couldn't find StopWatch code from the excercise page
// to measure the time for MC pricing computation
// kept the fucntion names and functionlity the same as what is required from the main/client code
class StopWatch
{
private:
    std::chrono::time_point<std::chrono::system_clock> start, end;

public:
    StopWatch() = default;
    StopWatch(const StopWatch& sw) = delete;
    StopWatch& operator=(const StopWatch& sw) = delete;

    void Start() {
        start = std::chrono::system_clock::now();
    }

    void Stop() {
        end = std::chrono::system_clock::now();
    }

    void Reset() {
        start = std::chrono::system_clock::now();
        end = start;
    }

    double GetTime() const {
        std::chrono::duration<double> elapsed_seconds = end - start;
        return elapsed_seconds.count();
    }

};