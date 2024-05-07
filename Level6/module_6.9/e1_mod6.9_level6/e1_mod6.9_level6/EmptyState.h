#pragma once
#ifndef EMPTYSTATE_H
#define EMPTYSTATE_H

#include "StackState.h"

template <typename T>
class EmptyState : public StackState<T> {
public:
    static std::shared_ptr<StackState<T>> getInstance();
    void push(Stack<T>& stack, T element) override;
    T pop(Stack<T>& stack) override;

private:
    static std::shared_ptr<StackState<T>> instance;
    EmptyState() {}
};

template <typename T>
std::shared_ptr<StackState<T>> EmptyState<T>::instance = nullptr;

#endif // EMPTYSTATE_H


