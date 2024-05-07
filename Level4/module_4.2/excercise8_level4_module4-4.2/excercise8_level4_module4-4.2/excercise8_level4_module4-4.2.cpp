#include <stack>
#include <algorithm>
#include <stdexcept>
#include <iostream>

template<typename T>
class CustomStack {
private:
    std::stack<T> s;

public:
    void push(T value) {
        s.push(value);
    }

    void max() {
        if (s.size() < 2) throw std::runtime_error("Not enough elements in the stack");
        T a = s.top(); s.pop();
        T b = s.top(); s.pop();
        s.push(std::max(a, b));
    }

    void min() {
        if (s.size() < 2) throw std::runtime_error("Not enough elements in the stack");
        T a = s.top(); s.pop();
        T b = s.top(); s.pop();
        s.push(std::min(a, b));
    }

    void over() {
        if (s.empty()) throw std::runtime_error("Stack is empty");
        T a = s.top(); s.pop();
        if (s.empty()) throw std::runtime_error("Not enough elements in the stack");
        T b = s.top();
        s.push(a);
        s.push(b);
    }

    void rot() {
        if (s.size() < 3) throw std::runtime_error("Not enough elements in the stack");
        T a = s.top(); s.pop();
        T b = s.top(); s.pop();
        T c = s.top(); s.pop();
        s.push(b);
        s.push(a);
        s.push(c);
    }

    void swap() {
        if (s.size() < 2) throw std::runtime_error("Not enough elements in the stack");
        T a = s.top(); s.pop();
        T b = s.top(); s.pop();
        s.push(a);
        s.push(b);
    }

    void drop() {
        if (s.empty()) throw std::runtime_error("Stack is empty");
        s.pop();
    }

    T top() {
        if (s.empty()) throw std::runtime_error("Stack is empty");
        return s.top();
    }
};

int main() {
    CustomStack<int> s;

    // push elements onto the stack
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);

    // test max operation
    s.max();
    std::cout << "After max operation: " << s.top() << std::endl;  // Should print 50

    // test min operation
    s.min();
    std::cout << "After min operation: " << s.top() << std::endl;  // Should print 40

    // test over operation
    s.over();
    std::cout << "After over operation: " << s.top() << std::endl;  // Should print 40

    // test rot operation
    s.rot();
    std::cout << "After rot operation: " << s.top() << std::endl;  // Should print 30

    // test swap operation
    s.swap();
    std::cout << "After swap operation: " << s.top() << std::endl;  // Should print 40

    // test drop operation
    s.drop();
    std::cout << "After drop operation: " << s.top() << std::endl;  // Should print 30

    /*
    Operations:
    max, min -> modifying
    over -> modifying
    rot -> mutating
    swap -> mutating
    drop -> modifying
    */

    return 0;
}
