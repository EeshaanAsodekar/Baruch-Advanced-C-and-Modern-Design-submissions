#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <functional>

// Subquestion (a)
// function to print a string a number of times
void Iprint(const std::string& s, int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << "Thread " << std::this_thread::get_id() << ": " << s << std::endl;
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    // callable objects
    // Subquestion (a)
    auto lambda = [](std::string s, int count)-> void { Iprint(s, count); };
    auto binded_func = std::bind(Iprint, std::placeholders::_1, std::placeholders::_2);
    struct Functor { void operator()(const std::string& s, int count) { Iprint(s, count); } } functor;

    // Subquestion (b)
    std::thread t1(Iprint, "Hello from free function", 5);
    std::thread t2(lambda, "Hello from stored lambda", 5);
    std::thread t3(functor, "Hello from functor", 5);
    std::thread t4(binded_func, "Hello from binded function", 5);

    // detached thread
    std::thread t5(Iprint, "Hello from detached thread", 5);
    t5.detach();

    // joining threads
    // Subquestion (c)
    // Join threads
    try {
        if (t1.joinable()) t1.join();
        if (t2.joinable()) t2.join();
        if (t3.joinable()) t3.join();
        if (t4.joinable()) t4.join();
    }
    catch (const std::exception& e) {
        std::cerr << "A thread could not be joined: " << e.what() << '\n';
        try {
            if (t1.joinable()) t1.join();
            if (t2.joinable()) t2.join();
            if (t3.joinable()) t3.join();
            if (t4.joinable()) t4.join();
        }
        catch (const std::exception& e) {
            std::cerr << "A thread could not be joined even in the catch block!\n seriours issue!" << e.what() << '\n';
        }
    }

    
    // Subquestion (f)
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds.\n";

    return 0;
}

/* Question> Examine the output; what do you see? What is happening?
* 
* All the threads are executing their respective fucntions concurrently. 
* This means that the output on the console may vary each time the program is run.
* Also, the we may or may not see the output of the detached thread, depending on 
* whether or not its execution ends before the main thread.
* 
*/
