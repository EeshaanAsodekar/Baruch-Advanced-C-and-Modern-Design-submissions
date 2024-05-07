#pragma once
#include "Observer.h"
#include "Subject.h"
#include "Counter.h"
#include <iostream>
#include <iomanip>


// Subquestion (k)
class LongFormat : public Observer
{
private:
	Counter* counter;
public:
	LongFormat(Counter* ctr) : counter(ctr) {
		counter->Attach(this);
	}
	void Update(Subject* subject) {
		if (subject == counter) {
			std::cout << "updated LongFormat!";
			std::cout << std::fixed << std::setprecision(2)
				<< static_cast<long>(counter->GetCounter()) << std::endl;
		}
	}
};

