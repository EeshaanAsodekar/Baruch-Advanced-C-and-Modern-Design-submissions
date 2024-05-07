#pragma once
#include "Subject.h"

// Subquestion (b): Counter class that derives from the Subject class
class Counter: public Subject
{
private:
	// Subquestion (c): private variable that holds the counter value
	long double value;
public:
	// Subquestion (h)
	Counter():value(0.0){} // initializing the counter to zero

	// Subquestion (e)
	long double GetCounter();

	// Subquestion (f)
	void IncreaseCounter();

	// Subquestion (g)
	void DecreaseCounter();
};

