#pragma once

#include <memory>
#include <vector>

class Observer;

// Subquestion (a)
class Subject
{
private:
    std::vector<Observer*> observers;

public:
    // adds an observer to the list
    void Attach(Observer* observer);

    // removes observer from the list
    void Detach(Observer* observer);

    // calls Update() on the observers on the list
    void Notify();
};

