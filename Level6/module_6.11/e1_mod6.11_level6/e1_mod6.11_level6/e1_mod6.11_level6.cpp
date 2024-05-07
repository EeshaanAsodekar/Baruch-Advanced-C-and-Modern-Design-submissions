#include <iostream>
#include "Counter.h"
#include "LongFormat.h"
#include "DoubleFormat.h"

// Subquestion (i)
void testCounterObserver() {

    Counter* counter = new Counter();

    LongFormat longObserver1(counter);
    LongFormat longObserver2(counter);
    DoubleFormat doubleObserver1(counter);
    DoubleFormat doubleObserver2(counter);

    counter->Attach(&longObserver1);
    counter->Attach(&longObserver2);
    counter->Attach(&doubleObserver1);
    counter->Attach(&doubleObserver2);

    // Testing increase functionality multiple times
    std::cout << "Testing multiple IncreaseCounter() calls:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        counter->IncreaseCounter(); // All observers will display the counter value
    }

    // Testing decrease functionality multiple times
    std::cout << "\n\n\nTesting multiple DecreaseCounter() calls:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        counter->DecreaseCounter(); // All observers will display the counter value
    }

    // Detaching observers one by one
    std::cout << "Detaching observers one by one and testing:" << std::endl;
    counter->Detach(&longObserver1);
    counter->IncreaseCounter(); // Remaining observers display the counter value
    counter->Detach(&doubleObserver1);
    counter->DecreaseCounter(); // Further remaining observers display the counter value

    // Attempting to detach an observer that was never attached
    std::cout << "Attempting to detach an observer that was never attached:" << std::endl;
    LongFormat unattachedObserver(counter);
    counter->Detach(&unattachedObserver); // Should have no effect on the notification system
    counter->IncreaseCounter();

    delete counter;
}

int main() {
    testCounterObserver();
    return 0;
}
