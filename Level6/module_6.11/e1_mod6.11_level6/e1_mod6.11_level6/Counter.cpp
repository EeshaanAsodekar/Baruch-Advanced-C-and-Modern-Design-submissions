#include "Counter.h"

long double Counter::GetCounter() {
	return value;
}
void Counter::IncreaseCounter() {
	value++;
	Notify();
}
void Counter::DecreaseCounter() {
	value--;
	Notify();
}
