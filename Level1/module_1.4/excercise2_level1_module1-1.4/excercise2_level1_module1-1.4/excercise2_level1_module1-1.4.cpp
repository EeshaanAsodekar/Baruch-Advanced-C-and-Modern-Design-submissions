#include <iostream>
#include <functional>
using namespace std;

// given test function
double freeFunction3(double x, double y, double z);

int main()
{
	// Subquestion (a) and (b)
	// defining and testing fucntions of arity 3,2,1,0
	auto arity3_freeFunction3 = freeFunction3;
	cout << "arity3_freeFunction3(1,2,3): " << arity3_freeFunction3(1, 2, 3) << "\n" << endl;

	auto arity2_freeFunction3 = bind(freeFunction3,1.0,placeholders::_1,placeholders::_2);
	cout << "arity2_freeFunction3(2,3): " << arity2_freeFunction3(2, 3) << "\n" << endl;

	auto arity1_freeFunction3 = bind(freeFunction3, 1.0, 2.0, placeholders::_1);
	cout << "arity1_freeFunction3(3): " << arity1_freeFunction3(3) << "\n" << endl;

	auto arity0_freeFunction3 = bind(freeFunction3, 1.0, 2.0, 3.0);
	cout << "arity0_freeFunction3(): " << arity0_freeFunction3() << "\n" << endl;

	// 1.0 + 2.0 + 3.0 = 6
	// output is correct

	return 0;
}

double freeFunction3(double x, double y, double z)
{
	return x + y + z;
}
