#include "NotFullNotEmptyState.h"
#include "EmptyState.h"
#include "FullState.h"

#include <stdexcept>

template <typename T>
std::shared_ptr<StackState<T>> NotFullNotEmptyState<T>::getInstance() {
    if (instance == nullptr) {
        instance = std::make_shared<NotFullNotEmptyState<T>>();
    }
    return instance;
}

template <typename T>
void NotFullNotEmptyState<T>::push(Stack<T>& stack, T element) {
    stack.elements[++stack.currentIndex] = element;
    if (stack.currentIndex == stack.elements.size() - 1) {
        stack.state = FullState<T>::getInstance();
    }
}

template <typename T>
T NotFullNotEmptyState<T>::pop(Stack<T>& stack) {
    T element = stack.elements[stack.currentIndex--];
    if (stack.currentIndex == -1) {
        stack.state = EmptyState<T>::getInstance();
    }
    return element;
}

template class NotFullNotEmptyState<int>;
