#pragma once
#include <list>

class Observable
{
protected:
    std::list<Observable*> observable_list;

public:
    // adds an observer to the list
    void AddObserver(Observable* observer);

    // removes observer from the list
    void DeleteObserver(Observable* observer);

    // calls Update() on the observers on the list
    virtual void NotifyObservers();

    virtual void Update(Observable* observer) = 0;
};
