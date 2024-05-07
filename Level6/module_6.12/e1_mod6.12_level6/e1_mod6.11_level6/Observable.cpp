#include <iostream>
#include "Observable.h"

// adds an observer to the list
void Observable::AddObserver(Observable* observer) {
	observable_list.push_back(observer);
}

// removes observer from the list
void Observable::DeleteObserver(Observable* observer) {
	observable_list.remove(observer);
}

// calls Update() on the observers on the list
void Observable::NotifyObservers() {
	for (Observable* observer : observable_list) {
		observer->Update(this);
		observer->NotifyObservers();
	}
}