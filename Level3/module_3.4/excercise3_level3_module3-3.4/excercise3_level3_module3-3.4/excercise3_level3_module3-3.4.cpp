#include <iostream>
#include <future>
#include <random>

// Subquestion (c)
template <typename T>
void DoubleFutureState(std::future<T>& fut)
{ 
    // thread function
    T t = fut.get(); // get the result of the future

    // introducing random delay to simulate some code being executed
    std::default_random_engine dre(42);
    std::uniform_int_distribution<int> delay(0, 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay(dre)));

    // printing to the console twice the value of the shared data to the future
    std::cout << "Double Value: " << 2*t << std::endl;
}

int main()
{
    // Subquestion (a)
    // default promise
    std::promise<int> prom1;

    // promise with an empty shared state
    // promise constructed with no value or exception set for it yet; thus "empty shared state"
    std::promise<int> prom2 = std::promise<int>();

    // Promise based on the move constructor
    std::promise<int> prom3 = std::promise<int>(std::move(prom1));


    // Subquestion (b)
    std::promise<double> prom4_double; // promise with double as stored value
    std::future<double> fut4_double = prom4_double.get_future();// a future that is associated with the promise.

    // Subquestion (c)
    //  Start a thread with the new future from part (b)
    std::thread myThread(DoubleFutureState<double>, std::ref(fut4_double));
    // the function DoubleFutureState uses the value of the shared data

    // Subquestion (d)
    // using the promise to set the value of the shared data
    prom4_double.set_value(4.0);

    myThread.join();

    return 0;
}
