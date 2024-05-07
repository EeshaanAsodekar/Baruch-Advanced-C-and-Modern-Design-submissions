#include <iostream>
#include <future>

// Subquestion (a)
void func1()
{
    // to show that this function is being executed:
    std::cout << "\nHello from fucn1\n";

    return;
}

double func2(double a, double b)
{
    // to show that this function is being executed:
    std::cout << "\nHello from fucn2\n";

    // returning the addition of the two inputs
    return a + b;
}

int main()
{   
    // launch func1
    auto fut1 = std::async(func1);
    // check validity
    std::cout << "fut1 valid: " << fut1.valid() << "\n";
    // get result (no result for func1 since it's void)
    fut1.get();
    // check validity again
    std::cout << "fut1 valid: " << fut1.valid() << "\n";

    // launch func2
    auto fut2 = std::async(func2, 3.0, 4.0);
    // check validity
    std::cout << "fut2 valid: " << fut2.valid() << "\n";
    // get and print result
    std::cout << "fut2 result: " << fut2.get() << "\n";
    // check validity again
    std::cout << "fut2 valid: " << fut2.valid() << "\n";

    // Subquestion (c)
    // If we try to get the result of a std::future more than once, we will get a runtime error. 
    // Once get() has been called, the std::future becomes invalid and cannot be used again.
    try {
        double result = fut2.get();
    }
    catch (const std::future_error& e) {// catching the future error that will be thrown
        if (e.code() == std::make_error_condition(std::future_errc::no_state)) {// the specific error condition
            std::cout << "Caught a future_error: No associated state\n";
        }
        else {
            std::cout << "Caught a future_error: " << e.what() << '\n';
        }
    }

    // Subquestion (d)
    // Launch func3 asynchronously
    auto fut3 = std::async(std::launch::async, func1);
    // Launch func4 asynchronously
    auto fut4 = std::async(std::launch::async, func2, 3.0, 4.0);

    /*
    * The difference:
    * If we specify std::launch::async as the launch policy for std::async, 
    * it guarantees that the function will run on a new thread. 
    * Without specifying this, the function may run either synchronously on 
    * the current thread or asynchronously on a new thread, depending on the implementation. 
    */

    // Subquestion (e)
    // Defer execution of func5
    auto fut5 = std::async(std::launch::deferred, func1);
    // Defer execution of func6
    auto fut6 = std::async(std::launch::deferred, func2, 3.0, 4.0);

    // 
    // some code which executes...
    // 
    
    // now we want to execute func1 and func2
    try {
        fut5.get();  // this will now execute func5
        double result = fut6.get();  // this will now execute func6 and return the result
        std::cout << "Result from func6: " << result << std::endl; // same as before
    }
    catch (const std::future_error& e) {// to catch if the .get() function has been previouly used
        std::cout << "Caught a future_error: " << e.what() << '\n';
    }

    return 0;
}
