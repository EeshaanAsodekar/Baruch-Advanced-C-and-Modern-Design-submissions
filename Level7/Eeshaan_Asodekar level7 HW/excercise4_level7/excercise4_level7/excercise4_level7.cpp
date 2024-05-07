#include <iostream>
#include <functional>
#include <future>
#include <vector>
#include "additionalFucntions.h"

// Given function categories
template <typename T>
using FactoryFunction = std::function<T()>;
template <typename T>
using ComputeFunction = std::function<T(const T&)>;
template <typename T>
using DispatchFunction = std::function<void(T&)>;

// Given class with Input-Processing-Output
template <typename T>
class TmpProcessor {
private:
    FactoryFunction<T> _factory;
    ComputeFunction<T> _compute;
    DispatchFunction<T> _dispatch;

public:
    TmpProcessor(const FactoryFunction<T>& factory,
        const ComputeFunction<T>& compute,
        const DispatchFunction<T>& dispatch)
        : _factory(factory), _compute(compute), _dispatch(dispatch) {}

    virtual void algorithm() final {
        T val = _factory();
        T val2 = _compute(val);
        _dispatch(val2);
    }
};

void testing() {
    // Subquestion (a): Testing with simple functions using lambda expressions
    TmpProcessor<int> processor([]() { return 5; },
        [](int x) { return x * x; },
        [](int& x) { std::cout << "Result: " << x << std::endl; });

    processor.algorithm(); // Executes factory, compute, and dispatch steps sequentially

    // Subquestion (b): Parallel processing using futures for compute-intensive tasks
    TmpProcessor<std::vector<int>> parallelProcessor(
        []() { return std::vector<int>{1, 2, 3, 4, 5}; },
        [](const std::vector<int>& v) {
            std::vector<std::future<int>> futures;
            for (int x : v) {
                futures.push_back(std::async(std::launch::async, [x]() { return x * x; }));
            }
            std::vector<int> results;
            for (auto& f : futures) {
                results.push_back(f.get());
            }
            return results;
        },
        [](std::vector<int>& v) {
            std::cout << "Parallel Results: ";
            for (int x : v) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        });

    // Subquestion (b): Sequential processing for comparison
    TmpProcessor<std::vector<int>> sequentialProcessor(
        []() { return std::vector<int>{1, 2, 3, 4, 5}; },
        [](const std::vector<int>& v) {
            std::vector<int> results;
            for (int x : v) {
                results.push_back(x * x);
            }
            return results;
        },
        [](std::vector<int>& v) {
            std::cout << "Sequential Results: ";
            for (int x : v) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        });

    parallelProcessor.algorithm(); 
    sequentialProcessor.algorithm(); 

    // Additional testing with floating-point numbers
    TmpProcessor<double> floatProcessor([]() { return 3.14; },
        [](double x) { return x * x; },
        [](double& x) { std::cout << "Float Result: " << x << std::endl; });
    floatProcessor.algorithm();
}

// Subquestion (b): more testing with complicated fucntion blocks
void testing2() {
    double initial_value = 10.0;

    // Sequential processing
    TmpProcessor<double> sequentialProcessor(
        [initial_value]() { return initial_value; },
        [](double a) {
            double b = function1(a);
            double c = function2(a);
            double d = function3(b + c);
            return d;
        },
        [](const double& result) {
            std::cout << "Sequential result: " << result << std::endl;
        }
    );

    // Parallel processing
    TmpProcessor<double> parallelProcessor(
        [initial_value]() { return initial_value; },
        [](double a) {
            auto futureB = std::async(std::launch::async, function1<double>, a);
            auto futureC = std::async(std::launch::async, function2<double>, a);
            double b = futureB.get();
            double c = futureC.get();
            double d = function3(b + c);
            return d;
        },
        [](const double& result) {
            std::cout << "Parallel result: " << result << std::endl;
        }
    );

    sequentialProcessor.algorithm();
    parallelProcessor.algorithm();
}

int main() {
    testing();
    testing2();
    return 0;
}

/*data dependency graph:

a   -> b = fucntion1(a)
    -> c = fucntion2(a)

b   -> d = fucntion3(b,c)
AND
c   -> d = fucntion3(b,c)
*/