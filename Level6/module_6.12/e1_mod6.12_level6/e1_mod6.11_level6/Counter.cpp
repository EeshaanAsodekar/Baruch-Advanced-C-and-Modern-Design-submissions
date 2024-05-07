#include "Counter.h"
#include "Observable.h"
#include <iostream>

long double Counter::GetCounter() {
	return value;
}
void Counter::IncreaseCounter() {
	value++;
	Update(this);
	NotifyObservers();
}
void Counter::DecreaseCounter() {
	value--;
	NotifyObservers();
}

// adds an observer to the list
void Counter::AddObserver(Observable* observer) {
	observable_list.push_back(observer);
}

//removes observer from the list
void Counter::DeleteObserver(Observable* observer) {
	observable_list.remove(observer);
}

// calls Update() on the observers on the list
void Counter::NotifyObservers() {
	for (Observable* observer : observable_list) {
		observer->Update(this);
	}
}

void Counter::Update(Observable* observer) {
	std::cout << "Updated" << std::endl;
}
