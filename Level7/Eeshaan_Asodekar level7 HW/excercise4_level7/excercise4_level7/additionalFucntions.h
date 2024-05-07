#pragma once

#include <iostream>
#include <tuple>
#include <vector>
#include <functional>
#include <future>
#include <thread>
#include <random>

// Function templates for simulating tasks of different complexities
template <typename T>
T function1(T input) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen)));
    return input + 10;
}

template <typename T>
T function2(T input) {
    return input * 2;
}

template <typename T>
T function3(T input) {
    for (int i = 0; i < 100000; ++i) {
        input += i % 5;
    }
    return input;
}