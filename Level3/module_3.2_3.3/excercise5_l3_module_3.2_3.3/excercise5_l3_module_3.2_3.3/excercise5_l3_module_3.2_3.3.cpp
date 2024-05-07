#include <string>
#include <mutex>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <atomic>

/// <summary>
/// Here the Producer class simulates the customers coming in for  a haircut; new customer every 10 seconds.
/// 
/// Consumer class simulates the barber working on a customer
/// 
/// The SynchronisedQueue is used to simulate the pipeline of the interested customers
/// 
/// Lecture 3-3.2 used as reference for this excercise
/// </summary>

std::atomic<bool> stopFlag(false);
std::mutex mutex_global;

int n = 3;

template <typename T>
class SynchronisedQueue
{
private:
    std::queue<T> m_queue; // Use STL queue to store data
    std::mutex m_mutex; // The mutex to synchronise on
    std::condition_variable m_cond; // The condition to wait for

public:
    // Add data to the queue and notify others
    void Enqueue(const T& data)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(data);
        m_cond.notify_one();
    }

    // Get data from the queue. Wait for data if not available
    T Dequeue()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_queue.size() == 0 && !stopFlag) {
            m_cond.wait(lock);
        }
        T result;
        if (!m_queue.empty()) {
            result = m_queue.front();
            m_queue.pop();
        }
        return result;
    }

    int size() {
        return m_queue.size();
    }
};

// Class that produces objects and puts them in a queue
class Producer
{
private:
    int m_id; // The id of the producer
    SynchronisedQueue<std::string>* m_queue; // The queue to use

public:
    // Constructor with id and the queue to use
    Producer(int id, SynchronisedQueue<std::string>* queue)
    {
        m_id = id; m_queue = queue;
    }

    // The thread function fills the queue with data
    void operator () ()
    {
        int data = 0;
        while (!stopFlag)
        {
            // Produce a string and store in the queue
            std::string str = "customer" + std::to_string(data++);
            std::cout << "\ncustomer number " << data << " wants a haircut\n";

            if (m_queue->size() < n) {
                std::cout << "\ncustomer number " << data << " in line for a haircut\n";
                m_queue->Enqueue(str);
            }
            else {
                std::cout << "\nbarber shop is full; customer number " << data << " leaves\n";
            }

            // Sleep ten seconds -> the next customer arrives in 10 seconds
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }
};

// Class that consumes objects from a queue
class Consumer
{
private:
    int m_id; // The id of the consumer
    SynchronisedQueue<std::string>* m_queue; // The queue to use

public:
    // Constructor with id and the queue to use
    Consumer(int id, SynchronisedQueue<std::string>* queue)
    {
        m_id = id; m_queue = queue;
    }

    // The thread function reads data from the queue
    void operator () ()
    {
        while (!stopFlag)
        {
            // Get the data from the queue and print it
            std::string data = m_queue->Dequeue();

            //std::unique_lock<std::mutex> lock(mutex_global);

            if (!data.empty()) {// if there are any customers
                std::cout << "\nbarber working on customer number: " << data.c_str() << std::endl;

                // it takes 30 seconds to work on one customer
                std::this_thread::sleep_for(std::chrono::seconds(30));

                std::cout << "\nbarber finished with customer number : (" << data.c_str() << ") and he leaves" << std::endl;
            }
        }
    }
};

int main() {
    SynchronisedQueue<std::string> queue;
    Producer interested_customers(0, &queue);
    std::thread cust(interested_customers);
    
    Consumer theBarber(0, &queue);
    std::thread barber(theBarber);

    // Wait for enter
    getchar();

    // Interrupt the threads and stop them
    stopFlag = true;
    
    cust.join();
    barber.join();

    return 0;
}
