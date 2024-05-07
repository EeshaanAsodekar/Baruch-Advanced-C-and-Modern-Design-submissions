#ifndef STACKSTATE_H
#define STACKSTATE_H

#include <memory>

template <typename T>
class Stack; // Forward declaration

// Subquestion (j)
template <typename T>
class StackState {
public:
    virtual ~StackState() {}
    virtual void push(Stack<T>& stack, T element) = 0;
    virtual T pop(Stack<T>& stack) = 0;

protected:
    StackState() = default;
};

#endif // STACKSTATE_H
