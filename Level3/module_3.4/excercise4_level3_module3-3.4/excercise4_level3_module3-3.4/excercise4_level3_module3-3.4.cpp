#include <iostream>
#include <thread>
#include <random>
#include <future>
#include <queue>
#include <vector>

// Subquestion (a)
double compute(double x, double y)
{
    // Wait a while
    std::default_random_engine dre(42);
    std::uniform_int_distribution<int> delay(0, 1000);
    std::this_thread::sleep_for
    (std::chrono::milliseconds(delay(dre)));

    return std::cos(x) * std::exp(y);
}

int main()
{
    // Subquestion (a)
    double x = 0; double y = 2.71;
    // A. 'Direct' tasks
    std::future<double> fut = std::async(compute, x, y);

    // Get the shared data
    double result = fut.get();

    std::cout << "Result: " << result << '\n';

    // Subquestion (b)
    std::packaged_task<double()> myTask(std::bind(compute,x,y));
    auto fut2 = myTask.get_future();

    myTask();

    // Wait for task to end and process result
    std::cout << "Result (delayed execution): " << fut2.get() << std::endl;


    // Subquestion (c)
    std::queue<std::packaged_task<double()>> tasks;

    // creating some tasks and add them to the queue
    for (int i = 0; i < 5; ++i) {
        std::packaged_task<double()> task(std::bind(compute, i, y));
        tasks.push(std::move(task));
    }

    int count = 0;
    // dequeueing each task and executing it
    while (!tasks.empty()) {
        std::packaged_task<double()>& task = tasks.front();
        task();
        std::future<double> curr_fut = task.get_future();
        std::cout << "Result (queued execution): " << curr_fut.get() << std::endl;
        tasks.pop();
        count++;
    }

    return 0;
}
