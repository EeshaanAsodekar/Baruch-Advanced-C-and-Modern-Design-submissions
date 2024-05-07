#include <iostream>
#include <future>

int main()
{
    // Subquestion (a)
    // default instance
    std::shared_future<int> sf1;

    // as a shared future that shares the same state as another shared state
    std::promise<int> prom1;
    std::shared_future<int> sf2 = prom1.get_future();

    // transfer shared state from a 'normal' future to a shared future
    std::promise<int> prom2;
    std::future<int> fut = prom2.get_future();// normal future
    std::shared_future<int> sf3 = std::move(fut);// shared future

    // transfer shared state from a shared future to a shared future
    std::shared_future<int> sf4 = sf3;

    // Subquestion (b)
    /*
    * Most member functions of std::future are also applicable to std::shared_future, 
    * including get(), valid(), wait(), wait_for(), and wait_until(). 
    * 
    * Apart from that shared futures are copyable and the get() fucntion can be 
    * called on them multiple times
    */

    std::promise<int> prom;
    std::shared_future<int> sf = prom.get_future();

    // check if the shared_future is valid
    std::cout << "Is sf valid? " << (sf.valid() ? "Yes" : "No") << "\n";

    // set the value of the promise
    prom.set_value(42);

    // now the shared_future is ready, so we can wait on it
    sf.wait();

    // you can also use wait_for and wait_until
    if (sf.wait_for(std::chrono::seconds(1)) == std::future_status::timeout) {
        std::cout << "Timeout occurred\n";
    }
    else {
        std::cout << "Shared future is ready\n";
    }

    // now the shared_future is ready, so wait_until will not block
    // but we can use wait_until on shared future as well
    sf.wait_until(std::chrono::system_clock::now() + std::chrono::seconds(1));

    // Subquestion (c)
    std::cout << "\nusing sf.get() first time : " << sf.get() << std::endl;
    std::cout << "\nusing sf.get() second time: " << sf.get() << std::endl;
    // we can use the .get() fucntion on a shared future multiple number of times (unlike on std::future)
    // the value that we get from it remains the same.

    // Subquestion (d)
    std::promise<void> prom3;
    std::shared_future<void> sf_3 = prom3.get_future();

    // start a new thread that runs an infinite loop
    // we are wating for the associated promise to be fulfilled; which is never is in the given code
    std::thread t([&]()->void {
        auto now = std::chrono::system_clock::now();
        while (sf_3.wait_until(now+std::chrono::milliseconds(1)) != std::future_status::ready) {
            // loop until the promise is fulfilled (it never is)
        }
        });

    // wait for the infinite loop to finish (which it never does)
    if (sf_3.wait_for(std::chrono::seconds(1)) == std::future_status::timeout) {
        std::cout << "Timeout; shared future was waiting on an infinite loop to finish\n";
    }
    else {
        std::cout << "Finished\n";
    }

    t.detach();  // detach the thread since it will never finish
    return 0;
}
