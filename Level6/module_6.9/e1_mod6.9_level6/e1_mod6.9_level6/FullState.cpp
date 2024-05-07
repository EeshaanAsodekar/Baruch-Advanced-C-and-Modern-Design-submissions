#include "FullState.h"
#include "NotFullNotEmptyState.h"

#include <stdexcept>

template <typename T>
std::shared_ptr<StackState<T>> FullState<T>::getInstance() {
    if (instance == nullptr) {
        instance = std::make_shared<FullState<T>>();
    }
    return instance;
}

template <typename T>
void FullState<T>::push(Stack<T>& stack, T element) {
    throw std::overflow_error("Stack is full. Cannot push new elements.");
}

template <typename T>
T FullState<T>::pop(Stack<T>& stack) {
    T element = stack.elements[stack.currentIndex--];
    if (stack.currentIndex == -1) {
        stack.state = EmptyState<T>::getInstance();
    }
    else {
        stack.state = NotFullNotEmptyState<T>::getInstance();
    }
    return element;
}

template class FullState<int>;
