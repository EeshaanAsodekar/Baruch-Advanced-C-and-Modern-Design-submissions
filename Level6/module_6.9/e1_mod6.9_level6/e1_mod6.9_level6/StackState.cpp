#include "StackState.h"
#include "Stack.h"
#include "EmptyState.h"
#include "NotFullNotEmptyState.h"
#include "FullState.h"

template <typename T>
Stack<T>::Stack(int size) {
    init(size);
}

template <typename T>
void Stack<T>::init(int size) {
    if (size < 1) size = 1;
    elements.resize(size);
    currentIndex = 0; // Stack is empty initially
    state = EmptyState<T>::getInstance();
}

template <typename T>
void Stack<T>::push(T element) {
    state->push(*this, element);
}

template <typename T>
T Stack<T>::pop() {
    return state->pop(*this);
}

template class Stack<int>;
