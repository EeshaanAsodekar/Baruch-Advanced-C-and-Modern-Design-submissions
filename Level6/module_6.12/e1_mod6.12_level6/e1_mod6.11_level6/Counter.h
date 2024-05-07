#pragma once
#include "Observable.h"

class Counter: public Observable
{
private:
	long double value;
public:
	Counter():value(0.0){}

	long double GetCounter();

	void IncreaseCounter();

	void DecreaseCounter();

	// adds an observer to the list
	void AddObserver(Observable* observer);

	//removes observer from the list
	void DeleteObserver(Observable* observer);

	// calls Update() on the observers on the list
	void NotifyObservers();

	virtual void Update(Observable* observer);
};

