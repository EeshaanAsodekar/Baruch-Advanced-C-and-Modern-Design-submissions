#include <iostream>
#include <thread>
#include <mutex>
#include <string>

// Subquestion (a)
// global data that is needed in order to implement this pattern

// Types and data needed
std::string data;// Shared data between master and worker
std::mutex m; // Ensures no race condition

// Synchronization between master and worker
std::condition_variable cv;

// Initial state of worker and master
//std::atomic<bool> workerReady = false;
//std::atomic<bool> masterReady = false;

std::atomic_flag workerReady = ATOMIC_FLAG_INIT;
std::atomic_flag masterReady = ATOMIC_FLAG_INIT;

// Worker
void Worker()
{
    std::cout << "Worker is called...\n";
    
    // acquring lock
    std::unique_lock<std::mutex> myLock(m);
    
    // wait until master sends data
    cv.wait(myLock, [&]()->bool{ return !workerReady.test_and_set(); });
    
    // now that master has given signal of workerReady = true
    std::cout << "Worker is now processing data\n";
    
    data += "worker work";
    
    // setting the masterReady flag to be true for futher processing
    // notifying the master
    masterReady.clear();

    // Postprocess
    myLock.unlock(); 

    // notifying the waiting master
    cv.notify_one();

    std::cout << "Exiting Worker\n";
}

int main()
{
    std::cout << "Master is called...\n";std::thread worker(Worker);
    data = "Master data";
    // Transition into True state
    {
        std::lock_guard<std::mutex> myLock(m);
        workerReady.clear();
    }
    std::cout << "Master has notified worker, wait for response...\n";
    cv.notify_one();
    {
        std::unique_lock<std::mutex> myLock(m);
        cv.wait(myLock, [&]() -> bool { return !masterReady.test_and_set(); });
    }
    std::cout << "back inside Master...\n";
    worker.join();

    return 0;
}
