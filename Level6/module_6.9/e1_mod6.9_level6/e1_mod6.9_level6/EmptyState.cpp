#include "EmptyState.h"
#include "FullState.h"
#include "NotFullNotEmptyState.h"
#include "Stack.h"
#include <stdexcept>

template <typename T>
class Stack;

//template <typename T>
//std::shared_ptr<StackState<T>> EmptyState<T>::instance = nullptr;

template <typename T>
std::shared_ptr<StackState<T>> EmptyState<T>::getInstance() {
    if (instance == nullptr) {
        instance = std::shared_ptr<EmptyState<T>>(new EmptyState<T>());
    }
    return instance;
}

template <typename T>
void EmptyState<T>::push(Stack<T>& stack, T element) {
    stack.elements[++stack.currentIndex] = element;
    if (stack.currentIndex == stack.elements.size() - 1) {
        stack.state = FullState<T>::getInstance();
    }
    else {
        stack.state = NotFullNotEmptyState<T>::getInstance();
    }
}

template <typename T>
T EmptyState<T>::pop(Stack<T>& stack) {
    throw std::underflow_error("Cannot pop from an empty stack.");
}

template class EmptyState<int>;
template class EmptyState<double>;
