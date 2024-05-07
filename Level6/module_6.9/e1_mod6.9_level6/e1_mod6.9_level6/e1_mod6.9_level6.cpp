#include <iostream>
#include "Stack.h"

// need more developement time
// the structure is ~95% perfect 
// but the 5% is causing structural errors
void testStack() {
    Stack<int> stack(10);
    try {
        for (int i = 0; i < 10; ++i) {
            std::cout << "Pushing: " << i << std::endl;
            stack.push(i);
        }

        for (int i = 0; i < 10; ++i) {
            std::cout << "Popping: " << stack.pop() << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

int main() {

    testStack();

    return 0;
}