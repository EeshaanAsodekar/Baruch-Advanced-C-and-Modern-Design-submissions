#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <random>
#include <vector>

// based on code given in lecture 3-3.1
// Priority Queue class that has thread synchronisation
// Subquestion (a)
template <typename T, 
    typename Container = std::vector<T>, //the default container is vector
    typename Compare = std::less<typename Container::value_type>> // default comparator is the std::less
class SynchronisedPriorityQueue
{
private:
    std::priority_queue<T, Container, Compare> priorityQ; // Use stl priority_queue to store data
    std::mutex m_mutex; // The mutex to synchronise on
    std::condition_variable m_cond; // The condition to wait for
public:
    // Add data to the pqueue and notify others
    void Enqueue(const T& data)
    {
        // Acquire lock on the pqueue
        // Subquestion (b)
        std::unique_lock<std::mutex> lock(m_mutex);
        // Add the data to the pqueue
        priorityQ.push(data);
        std::cout << "\nadded data:" << data << " onto SynchronisedPriorityQueue\n";
        // Notify others that data is ready
        m_cond.notify_one(); // Subquestion (c)
    } // Lock is released here

    // Get data from the pqueue. Wait for data if not available
    T Dequeue()
    {
        // Acquire lock on the pqueue
        // Subquestion (b)
        std::unique_lock<std::mutex> lock(m_mutex);
        // When there is no data, wait till someone fills it
        // Lock is automatically released in the wait and active again after the wait
        while (priorityQ.size() == 0) m_cond.wait(lock);
        // Retrieve the data from the pqueue
        T result = priorityQ.top(); priorityQ.pop();
        return result;
    } // Lock is released here
};

int main()
{
    // Subquestion (d)
    // Testing the new class designed
    SynchronisedPriorityQueue<int,std::vector<int>> synPriorityQ;
    // using the default std::less comparator
    // ofcourse, we can add our own custom comparator like: "[](int x, int y) {return 2*x>y; };"

    std::random_device rd;  // will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 10);

    std::cout << "adding 10 random integers between 0 and 10 onto the synPriorityQ\n";
    std::thread producer([&]() {
        for (int i = 0; i < 10; ++i) {
            synPriorityQ.Enqueue(distrib(gen));
            std::this_thread::sleep_for(std::chrono::microseconds(1)); // introducing delay to test multithreaded functioning
        }
        });

    std::thread consumer([&]() {
        for (int i = 0; i < 10; ++i) {
            int item = synPriorityQ.Dequeue();
            std::cout << "Dequeued: " << item << std::endl;
        }
        });

    producer.join();
    consumer.join();

    // the class works as expected. 
    // the dequeue fucntion waits till the the pqueue is of non-zero size, and
    // the pops off elements according to the comparator

    return 0;
}
