#pragma once
#include "Observer.h"
#include "Subject.h"
#include "Counter.h"
#include <iostream>
#include <iomanip>

// Subquestion (k)
class DoubleFormat :
    public Observer
{
private:
	Counter* counter;
public:
	DoubleFormat(Counter* ctr) : counter(ctr) {
		counter->Attach(this);
	}
	void Update(Subject* subject) {
		if (subject == counter) {
			std::cout << "updated DoubleFormat!";
			std::cout << std::fixed << std::setprecision(2)
				<< static_cast<double>(counter->GetCounter()) << std::endl;
		}
	}
};

