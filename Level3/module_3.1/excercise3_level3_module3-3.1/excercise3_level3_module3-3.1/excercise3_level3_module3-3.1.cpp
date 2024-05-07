#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>
#include <functional>
#include <system_error>

// uncomment the respective increment_counter() fucntion to test that approach of safe locking


std::mutex mutex_global; // this must be shared by all the threads
std::timed_mutex mutex_global_t; // this must be shared by all the threads
int count_failed_to_acquire_lock = 0;
int counter = 0;

// Subquestion (a)
//void increment_counter() {
//	std::lock_guard<std::mutex> guard(mutex_global);
//	++counter;
//	std::cout << "\nThread " << std::this_thread::get_id() << ": Counter: " << counter << std::endl;
//}

// Subquestion (c)
// counter may not be incremented to 4. 
// try_locK() does not wait to acquire the lock
//void increment_counter() {
//
//	std::unique_lock<std::mutex> lock(mutex_global, std::defer_lock);
//
//	try {
//		if (&mutex_global == nullptr) {// no associated mutex
//			throw std::system_error(std::make_error_code(std::errc::operation_not_permitted));
//		}
//		if (!lock.try_lock()) {// mutex already locked
//			throw std::system_error(std::make_error_code(std::errc::resource_unavailable_try_again));
//		}
//		else {
//			++counter;
//			std::cout << "\nThread " << std::this_thread::get_id() << ": Counter: " << counter << std::endl;
//		}
//		std::cout << "Mutex locked successfully with try_lock.\n";
//	}
//	catch (const std::system_error& e) {
//		std::cout << "System error while trying to lock: " << e.what() << '\n';
//	}
// 
// // Lock is released here
//}

// Subquestion (d)
//void increment_counter() {
//	std::unique_lock<std::timed_mutex> lock(mutex_global_t, std::defer_lock);
//	try {
//		if (&mutex_global == nullptr) {// no associated mutex
//			throw std::system_error(std::make_error_code(std::errc::operation_not_permitted));
//		}
//		if (lock.try_lock_for(std::chrono::seconds(1))) {// trying to acquire lock on mutex for 1 second
//			counter++;
//			std::cout << "\nThread " << std::this_thread::get_id() << ": Counter: " << counter << std::endl;
//		}
//		else {
//			std::cout << "\nThread " << std::this_thread::get_id() << ": Failed to acquire lock." << std::endl;
//			throw std::system_error(std::make_error_code(std::errc::resource_unavailable_try_again));
//		}
//	}
//	catch (const std::system_error& e) {
//		std::cout << "System error while trying to lock: " << e.what() << '\n';
//	}
// 
// //Lock is released here
//}

// Subquestion (e)
//void increment_counter() {
//	std::unique_lock<std::mutex> lock(mutex_global);
//	
//	// increment the counter
//	counter++;	
//	std::cout << "\nThread " << std::this_thread::get_id() << ": Counter: " << counter << std::endl;
//	try {
//		// unlock the mutex
//		lock.unlock();
//	}
//	catch (const std::system_error& e) {
//		std::cerr << "System error occurred while unlocking: " << e.what() << '\n';
//	}
//}

// subquestion (f)
void increment_counter() {
	std::unique_lock<std::timed_mutex> lock(mutex_global_t, std::defer_lock);
	auto now = std::chrono::steady_clock::now();
	auto timeout = now + std::chrono::seconds(10); // 10 seconds timeout

	try {
		// Try to acquire the lock until the timeout
		if (lock.try_lock_until(timeout)) {
			// Increment the counter
			counter++;
			std::cout << "\nThread " << std::this_thread::get_id() << ": Counter: " << counter << std::endl;
			// Unlock the mutex
			lock.unlock();
		}
		else {
			std::cerr << "Failed to acquire lock within timeout period.\n";
		}
	}
	catch (const std::system_error& e) {
		std::cerr << "System error occurred: " << e.what() << '\n';
	}
}

// Subquestion (g)
//void increment_counter() {
//	std::unique_lock<std::mutex> lock(mutex_global);
//	// Increment the counter
//	counter++;
//	std::cout << "\nThread " << std::this_thread::get_id() << ": Counter: " << counter << std::endl;
//
//	// Release the mutex without unlocking it
//	// this will cause the program to never end;
//	// the lock is never released; no other thread after the first thread can access it
//	lock.release();
//}


int main() {
	auto start = std::chrono::high_resolution_clock::now();

	// callable objects
	auto lambda = []()-> void { increment_counter(); };
	auto binded_func = std::bind(increment_counter);
	struct Functor { void operator()() { increment_counter(); } } functor;

	std::thread t1(increment_counter);
	std::thread t2(lambda);
	std::thread t3(functor);
	std::thread t4(binded_func);

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

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Elapsed time: " << elapsed.count() << " seconds.\n";
	std::cout << "final counter: " << counter;


	return 0;
}