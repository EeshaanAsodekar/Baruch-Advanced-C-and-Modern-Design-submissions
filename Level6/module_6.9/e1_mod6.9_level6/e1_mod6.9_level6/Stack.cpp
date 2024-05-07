#include "Stack.h"
#include "EmptyState.h"
#include "NotFullNotEmptyState.h"
#include "FullState.h"

// Subquestion (f)
template <typename T>
Stack<T>::Stack() {
    init(1);
}

// Subquestion (g)
template <typename T>
Stack<T>::Stack(int size) {
    init(size);
}

// Subquestion (e)
template <typename T>
void Stack<T>::init(int size) {
    if (size < 1) size = 1;
    elements.resize(size);
    currentIndex = 0;
    state = EmptyState<T>::getInstance();
}

// Subquestion (h)
template <typename T>
void Stack<T>::push(T element) {
    state->push(*this, element);
}

// Subquestion (i)
template <typename T>
T Stack<T>::pop() {
    return state->pop(*this);
}