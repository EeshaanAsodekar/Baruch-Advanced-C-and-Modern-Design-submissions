#ifndef FULLSTATE_H
#define FULLSTATE_H

#include "StackState.h"
#include "Stack.h"

template <typename T>
class FullState : public StackState<T> {
public:
    static std::shared_ptr<StackState<T>> getInstance();
    void push(Stack<T>& stack, T element) override;
    T pop(Stack<T>& stack) override;

private:
    static std::shared_ptr<StackState<T>> instance;
    FullState() {}
};

template <typename T>
std::shared_ptr<StackState<T>> FullState<T>::instance = nullptr;

#endif // FULLSTATE_H
