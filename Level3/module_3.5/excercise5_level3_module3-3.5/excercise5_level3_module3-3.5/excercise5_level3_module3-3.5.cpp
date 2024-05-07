#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <random>
#include <vector>
#include <string>
#include <chrono>
#include <functional>

using FunctionType = std::function<double(double)>;

class Command
{
private:
	long ID; // priority of command
	FunctionType algo;
public:
	Command(const FunctionType& algorithm, long priority)
		: algo(algorithm), ID(priority) {}

	void Execute(double x) {
		// Introduce delay to simulate a heavy algorithm
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		std::cout << algo(x) << '\n';
	}

	int priority() const
	{
		return ID;
	}
};

Command cmd1([](double x) -> double {return x * 0.025;}, 1);
Command cmd2([](double x) -> double {return x * 0.5;}, 2);
Command cmd3([](double x) -> double {return x;}, 3);
Command cmd4([](double x) -> double {return x * 2;}, 4);
Command cmd5([](double x) -> double {return x * 3;}, 5);
Command cmd6([](double x) -> double {return x * 4;}, 6);
Command cmd7([](double x) -> double {return x * 5;}, 7);

std::atomic<bool> stopFlag(false); // Flag to signal thread interruption

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

// Class that produces objects and puts them in a queue
class Producer
{
private:
	int m_id; // The id of the producer
	SynchronisedPriorityQueue<Command>* m_queue; // The queue to use
public:
	// Constructor with id and the queue to use
	Producer(int id, SynchronisedPriorityQueue<Command>* queue)
		: m_id(id), m_queue(queue) {}

	// The thread function fills the queue with data
	void operator () ()
	{
		int data = 0;
		while (!stopFlag)
		{
			// Produce a Command and store in the queue
			Command cmd([&](double x)-> double { return x * data; }, data);
			m_queue->Enqueue(cmd);
			std::cout << "Producer: " << m_id << " data: " << data++ << std::endl;
			// Sleep one second
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
};

class Consumer
{
private:
	int m_id; // The id of the consumer
	SynchronisedPriorityQueue<Command>* m_queue; // The queue to use
public:
	// Constructor with id and the queue to use
	Consumer(int id, SynchronisedPriorityQueue<Command>* queue)
		: m_id(id), m_queue(queue) {}

	// The thread function reads data from the queue
	void operator () ()
	{
		while (!stopFlag)
		{
			// Get the Command from the queue and execute it
			Command cmd = m_queue->Dequeue();
			std::cout << "Consumer " << m_id << " consumed: ";
			cmd.Execute(2.0);  // Assuming 2.0 as the input for the Command's function
		}
	}
};


int main()
{
	// The number of producers/consumers
	int nrProducers = 3, nrConsumers = 3;

	auto Command_comparator = [](Command cmd1_lhs, Command cmd2_rhs) {
		return cmd1_lhs.priority() < cmd2_rhs.priority();
		};

	// The shared queue
	SynchronisedPriorityQueue<Command, std::vector<Command>, decltype(Command_comparator)> queue(Command_comparator);

	// Create producers
	std::vector<std::thread> producers;
	for (int i = 0; i < nrProducers; i++)
	{
		Producer p(i, &queue);
		producers.push_back(std::thread(std::ref(p)));
	}

	// Create consumers
	std::vector<std::thread> consumers;
	for (int i = 0; i < nrConsumers; i++)
	{
		Consumer c(i, &queue);
		consumers.push_back(std::thread(std::ref(c)));
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