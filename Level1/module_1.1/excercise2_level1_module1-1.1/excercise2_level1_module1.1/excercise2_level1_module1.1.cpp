/*
	student: Eeshaan Asodekar
	email: epa6822@nyu.edu
	phone number: +1 347 881 5332

	submission for >> 1.1 Lambda Functions >> Exercise 2: Comparing Lambda Functions with Function Objects and Free Functions)
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <numeric>
#include <complex>
using namespace std;

// given
struct FOMultiply
{
	template <typename T>
	T operator () (const T& x, const T& y)
	{
		return x * y;
	}
};

// given
template <typename T>
T MyMultiply2(const T& x, const T& y) { return x * y; };

int main() {
	vector<int> vec{ 1,2,3,4,5 };
	// the given algorithm:
	int acc2 = std::accumulate(vec.begin(), vec.end(), 1,
		std::multiplies<int>());
	int accA = accumulate(vec.begin(), vec.end(), 1,
		FOMultiply());

	// Subquestion (a)
	cout << "Subquestion (a)\n\n";

	// given: N.B. Generic lambda
	auto MyMultiply = [](auto x, auto y) { return x * y;};

	// Implementing and testing the algorithm using the generic lambda fucntion 'MyMultiply'
	int accB = accumulate(vec.begin(), vec.end(), 1,
		MyMultiply);
	cout << "o/p of std::multiplies<int>() acc2: " << acc2 << endl;
	cout << "o/p of FOMultiply() accA: " << accA << endl;
	cout << "o/p of MyMultiply lambda fucntion accB: " << accB << endl;
	cout << endl;

	// part (a) section 2
	/*prompt given: 
	* Can the algorithm also be used with complex numbers, for example? 
	* Can we use function objects to multiply the elements of an array of complex numbers?
	*/
	cout << "Subquestion (b)\n\n";
	using Complex = std::complex<double>;
	std::vector<Complex> complexArray{ Complex(1.0, 1.0), Complex(2.0, 2.0) };
	Complex initCVal(1.0, 1.0);
	// auto acc6C = accumulate(complexArray.begin(), complexArray.end(),
	// initCVal, FOMultiply());
	Complex acc6C = accumulate(complexArray.begin(), complexArray.end(),
		initCVal, MyMultiply2<Complex>);
	std::cout << "o/p of template fucntion MyMultiply<Complex> acc6C: " << acc6C << std::endl;
	Complex acc6D = accumulate(complexArray.begin(), complexArray.end(),
		initCVal, FOMultiply());
	std::cout << "o/p of FOMultiply() acc6D: " << acc6C << std::endl;

	/*
	* from the above code we can clearly see the following:
	* yes, we can clearly see that the algorithm (with the help of the template fucntion MyMultiply2) can also
	* be used with complex numbers
	* and yes, we can also use fucntion objects to multiply the elements of an array of complex numbers
	*/

	// part (b)
	Complex complex_accumulator(1.0, 1.0);
	for_each(complexArray.begin(), complexArray.end(), [&complex_accumulator](Complex c1) {
		return complex_accumulator *= c1;
		});

	std::cout << "o/p of lambda fucntion complex_accumulator: " << complex_accumulator << std::endl;
	cout << endl;

	// Subquestion (c)
	cout << "Subquestion (c)\n\n";
	vector<int> arr = { 2,4,6,8,10};

	cout << "vector<int> arr:\n";
	for (auto itr = arr.begin(); itr != arr.end();itr++) {
		cout << *itr << "\t";
	}
	cout << endl;

	// our stored lambda function 'iseven' stores the logic of even or odd
	auto iseven = [](int i) -> bool {return i % 2 == 0;};

	// we are using the all_of() fucntion from the <algorithm> library
	// in essence, this function returns true or false if a particular condition is satisfied for all the
	// elements of in the given range
	// here we are checking if all the elements of the vector<int> arr are even or not
	// we are using the iseven stored lambda fucntion for the giving a true/false o/p on each element being even or not
	cout << "\nchecking if all the elements of arr are even...\n\n";
	if (all_of(arr.begin(), arr.end(), iseven))
		std::cout << "All the elements are even numbers.\n";
	return 0;
}