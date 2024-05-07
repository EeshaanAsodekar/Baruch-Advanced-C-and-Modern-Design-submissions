//why am I not gettint the output "process ended with 0" for this code:
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <vector>
#include <atomic>

std::atomic<bool> stopFlag(false); // Flag to signal thread interruption

// Queue class that has thread synchronisation
template <typename T>
class SynchronisedQueue
{
private:
	std::queue<T> m_queue; // Use stl queue to store data
	std::mutex m_mutex; // The mutex to synchronise on
	std::condition_variable m_cond; // The condition to wait for
public:
	// Add data to the queue and notify others
	void Enqueue(const T& data)
	{
		// Acquire lock on the queue
		std::unique_lock<std::mutex> lock(m_mutex);
		// Add the data to the queue
		m_queue.push(data);
		// Notify others that data is ready
		m_cond.notify_one();
	} // Lock is released here



	// Get data from the queue. Wait for data if not available
	T Dequeue()
	{
		// Acquire lock on the queue
		std::unique_lock<std::mutex> lock(m_mutex);
		// When there is no data, wait till someone fills it
		// Lock is automatically released in the wait and active again after the wait
		while (m_queue.size() == 0 && !stopFlag) m_cond.wait(lock);
		// If stopFlag is true, return default value
		if (stopFlag) return T();
		// Retrieve the data from the queue
		T result = m_queue.front(); m_queue.pop();
		return result;
	} // Lock is released here

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
			std::string str = "Producer: " + std::to_string(m_id) + " data: " + std::to_string(data++);
			m_queue->Enqueue(str);
			std::cout << str << std::endl;
			// Sleep one second
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
};

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
			std::cout << "Consumer " << std::to_string(m_id).c_str();
			std::cout << " consumed: (" << m_queue->Dequeue().c_str() << ")" << std::endl;

			// Make sure we can be interrupted
		}
	}
};

int main() {
	// The number of producers/consumers
	int nrProducers = 3, nrConsumers = 3;
	// The shared queue
	SynchronisedQueue<std::string> queue;

	// Create producers
	std::vector<std::thread> producers;
	for (int i = 0; i < nrProducers; i++)
	{
		Producer p(i, &queue);
		producers.push_back(std::thread(p));
	}

	// Create consumers
	std::vector<std::thread> consumers;
	for (int i = 0; i < nrConsumers; i++)
	{
		Consumer c(i, &queue);
		consumers.push_back(std::thread(c));
	}

	// Wait for enter
	char c = getchar();

	// Interrupt the threads and stop them
	stopFlag = true; // Set the stop flag to true

	// Join all producer threads
	for (auto& t : producers) {
		if (t.joinable()) {
			t.join();
		}
	}

	// Join all consumer threads
	for (auto& t : consumers) {
		if (t.joinable()) {
			t.join();
		}
	}

	return 0;
}