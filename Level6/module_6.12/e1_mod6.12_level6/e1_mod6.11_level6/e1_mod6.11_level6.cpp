#include <iostream>
#include "Counter.h"
#include "Observable.h"

// Can more more extesnive testing
//// Custom observer class to demonstrate the update mechanism
//class CustomObserver : public Observable {
//public:
//    void Update(Observable* observable) override {
//        Counter* counter = dynamic_cast<Counter*>(observable);
//        if (counter) {
//            std::cout << "CustomObserver sees Counter's value as: " << counter->GetCounter() << std::endl;
//        }
//    }
//};
//
//void testCounterObserver() {
//    Counter counter1;
//    Counter counter2;
//    Counter counter3;
//    CustomObserver customObserver;
//
//    // Have counter2 and customObserver observe counter1
//    std::cout << "Attaching counter2 and customObserver to counter1..." << std::endl;
//    counter1.AddObserver(&counter2);
//    counter1.AddObserver(&customObserver);
//
//    // Have counter3 observe counter2
//    std::cout << "Attaching counter3 to counter2..." << std::endl;
//    counter2.AddObserver(&counter3);
//
//    // Increase counter1, which will also update counter2 and customObserver, and then counter3
//    std::cout << "Increasing counter1, which will update its observers..." << std::endl;
//    counter1.IncreaseCounter();
//
//    // Verify that counter3 updated as well
//    std::cout << "Counter3 should have updated value due to counter2's update." << std::endl;
//    std::cout << "Final value of counter3: " << counter3.GetCounter() << std::endl;
//
//    // Detach counter2 and show that it no longer updates when counter1 is increased
//    std::cout << "Detaching counter2 from counter1 and increasing counter1..." << std::endl;
//    counter1.DeleteObserver(&counter2);
//    counter1.IncreaseCounter();
//
//    // Show final values to confirm that counter2 did not update
//    std::cout << "Final value of counter1: " << counter1.GetCounter() << std::endl;
//    std::cout << "Final value of counter2 (should not have changed): " << counter2.GetCounter() << std::endl;
//
//    // Increase counter2 to show it still updates counter3
//    std::cout << "Increasing counter2, which will update its observers (counter3)..." << std::endl;
//    counter2.IncreaseCounter();
//
//    // Output the final values of all counters
//    std::cout << "Final value of counter1: " << counter1.GetCounter() << std::endl;
//    std::cout << "Final value of counter2: " << counter2.GetCounter() << std::endl;
//    std::cout << "Final value of counter3: " << counter3.GetCounter() << std::endl;
//}

void testCounterObserver() {
    Counter counter1;
    Counter counter2;

    // Have counter2 observe counter1
    counter1.AddObserver(&counter2);

    // Increase counter1, which will also update counter2
    std::cout << "Increasing counter1..." << std::endl;
    counter1.IncreaseCounter();

    // Decrease counter2, which will not affect counter1 since counter1 is not observing counter2
    std::cout << "Decreasing counter2..." << std::endl;
    counter2.DecreaseCounter();

    // Output the final values of counter1 and counter2
    std::cout << "Final value of counter1: " << counter1.GetCounter() << std::endl;
    std::cout << "Final value of counter2: " << counter2.GetCounter() << std::endl;
}

int main() {
    testCounterObserver();
    return 0;
}
