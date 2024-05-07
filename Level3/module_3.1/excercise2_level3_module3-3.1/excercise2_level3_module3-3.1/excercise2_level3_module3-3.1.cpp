#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>
#include <functional>

// uncomment the respective Iprint() fucntion to test that approach of syncronization

std::mutex mutex_global;// this must be shared by all the threads
int count_failed_to_acquire_lock = 0;

// Subquestion (a)
// function to print a string a number of times
// using mutex lock and unlock
//void Iprint(const std::string& s, int count) {
//    mutex_global.lock();
//    for (int i = 0; i < count; ++i) {
//        std::cout << "\nThread " << std::this_thread::get_id() << ": " << s << std::endl;
//    }
//    mutex_global.unlock();
//}


// Subquestion (b)
// using mutex .try_lock()
void Iprint(const std::string& s, int count) {
    while (!mutex_global.try_lock()) {
        ++count_failed_to_acquire_lock;
    }
    for (int i = 0; i < count; ++i) {
        std::cout << "\nThread " << std::this_thread::get_id() << ": " << s << std::endl;
    }
    mutex_global.unlock();
}


// Subquestion (c)
// function to print a string a number of times
// using mutex lock and not unlocking (deadlock simulation)
//void Iprint(const std::string& s, int count) {
//    mutex_global.lock();
//    for (int i = 0; i < count; ++i) {
//        std::cout << "\nThread " << std::this_thread::get_id() << ": " << s << std::endl;
//    }
//
//}


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

    // detached thread -> cannot use a detached thread with the mutex variable on the main thread
    //std::thread t5(Iprint, "Hello from detached thread", 5);
    //t5.detach();

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
    std::cout << "\nfailed .try_lock() attempts:  " << count_failed_to_acquire_lock;

    return 0;
}

/* Answers to subjective questions: 
* 
* a) using mutex lock and unlock >>> 0.0111076 seconds
* b) using mutex .try_lock() >>> 0.0166339 seconds ; failed .try_lock() attempts:  120201
* c) uncommenting the mutex lock() and unlock() version of Iprint():
* The program goes on running till eternity. This is because in the main fucntion we wait for all the
* threads to complete their execution, but since the first thread deadlocks the printing to the console,
* none of the other threads are able to print to the console, and wait for lock to be unlocked. 
* But since the first thread that locks the mutex never unlocks it, these threads wait till eternity.
* Thus the program does not terminate, and will never terminate.
* 
*/