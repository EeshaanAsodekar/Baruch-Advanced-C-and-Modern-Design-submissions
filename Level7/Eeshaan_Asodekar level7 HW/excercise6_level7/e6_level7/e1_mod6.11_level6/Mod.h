#include <iostream>
#include <list>
#include <deque>
#include <functional>
#include <memory>
#include <iomanip>

// Subquestion (a) and (b)

// Modfied subject class
template<template<typename...> class Container = std::list>
class SubjectMod {
protected:
    // Using a pair of function and shared_ptr to flag to allow disabling observers
    Container<std::pair<std::function<void(double)>, std::shared_ptr<bool>>> observers;

public:
    // Attach returns a handle which signifies activate/deactivate observer
    std::shared_ptr<bool> Attach(std::function<void(double)> observer) {
        auto flag = std::make_shared<bool>(true); // Flag is true if observer is active
        observers.emplace_back(observer, flag);
        return flag;
    }

    // Detach is handled by deactivating the flag
    void Detach(std::shared_ptr<bool> handle) {
        *handle = false; // Set flag to false, deactivating the observer
    }

    void Notify(double value) {
        for (auto& observer : observers) {
            if (*observer.second) { // Check if the observer is active
                observer.first(value); // then updates it
            }
        }
    }
};



// Counter structure kept as simple as possible to implement the given requirements
// Uses std::deque as the container, demonstrating the templated container functionality

// modified counter class
class CounterMod : public SubjectMod<std::deque> {
private:
    double value = 0;

public:
    CounterMod() : value(0) {}

    void IncreaseCounter() {
        value += 0.1;  // Increment by 0.1
        Notify(value);
    }

    void DecreaseCounter() {
        value -= 0.1;  // Decrement by 0.1
        Notify(value);
    }

    double GetCounter() const {
        return value;
    }
};