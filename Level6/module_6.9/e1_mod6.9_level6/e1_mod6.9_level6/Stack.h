#ifndef STACK_H
#define STACK_H

#include "StackState.h"
#include <vector>
#include <memory>

// Subquestion (a): new class called Stack
template <typename T>
class Stack {
public:
    // Subquestion (f)
    Stack();

    // Subquestion (g)
    Stack(int size);

    // Subquestion (h)
    void push(T element);

    // Subquestion (i)
    T pop();

    // Subquestion (b): array to store its elements
    std::vector<T> elements;
    
    // Subquestion (c): private data-member for the current index.
    int currentIndex;
    
    // Subquestion (d): holds the current state
    std::shared_ptr<StackState<T>> state;
    
    // Subquestion (e): 
    void init(int size);
};

#include "EmptyState.h"
#include "NotFullNotEmptyState.h"
#include "FullState.h"

#endif // STACK_H
