#include <iostream>
#include <thread>
#include <random>
#include <chrono>
#include <array>
#include <mutex>

// given class
struct X
{
    double val;

    X() : val(0.0) {}
    void operator ()() {
        std::cout << "An X " << val << std::endl;
    }
};

// C++11
template <typename T>
using GenericPointerType = std::shared_ptr<T>;
using PointerType = GenericPointerType<X>;

std::mutex mtx;

// give function
void Modify(PointerType& p, double newVal)
{
    // Subquestion (a)
    // introducing delay by making the thread sleep for a random amount of time
    std::default_random_engine dre(42);
    std::uniform_int_distribution<int> delay(0, 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay(dre)));

    // updating the state
    p->val = newVal;

    // using lock_guard to print to the console the current value of the object
    // we want to avoid racing in the cout; we want to study racing in the value updation
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "\nnew value assigned: " << p->val << std::endl;
}

int main()
{
    PointerType p(new X);

    // Subqeuestion (b)
    std::array<std::thread, 100> threads;

    for (int i = 0; i < 100; ++i)
    {
        threads[i] = std::thread(Modify, std::ref(p), static_cast<double>(i));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    /*
    * Subquestion (c)
    * 
    * When we run the program multiple times, we’ll notice that the final value of p->val is non-deterministic. 
    * This is because the Modify function introduces a delay before updating the state, and multiple threads 
    * are trying to update the state at the same time. 
    * This results in a race condition, where the final value depends on which thread finishes last.
    * 
    * The “new value assigned” lines in the output are showing the value that each thread 
    * had tried to assign to p->val. However, because the threads are running concurrently, 
    * they might not finish in the order they were started. 
    * 
    * A thread that was started later (with a higher unique value) might finish before a thread 
    * that was started earlier (with a lower unique value). 
    * This is why we see the assigned values in the output are not in any particular order.
    * If a particular value is being printed with the highest frequency, then it must be the value
    * correspoding to the thread which finished last.
    */

    return 0;
}

