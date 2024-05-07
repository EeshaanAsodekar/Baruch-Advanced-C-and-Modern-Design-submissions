#pragma once
#ifndef NOTFULLNOTEMPTYSTATE_H
#define NOTFULLNOTEMPTYSTATE_H

#include "StackState.h"
#include "Stack.h"

template <typename T>
class NotFullNotEmptyState : public StackState<T> {
public:
    static std::shared_ptr<StackState<T>> getInstance();
    void push(Stack<T>& stack, T element) override;
    T pop(Stack<T>& stack) override;

private:
    static std::shared_ptr<StackState<T>> instance;
    NotFullNotEmptyState() {}
};

template <typename T>
std::shared_ptr<StackState<T>> NotFullNotEmptyState<T>::instance = nullptr;


#endif // NOTFULLNOTEMPTYSTATE_H
