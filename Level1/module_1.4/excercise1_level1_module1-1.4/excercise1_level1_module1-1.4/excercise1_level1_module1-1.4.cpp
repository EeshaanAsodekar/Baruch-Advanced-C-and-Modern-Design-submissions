#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

// Subquestion (a)
template <typename T>
using FunctionType = std::function<T(const T& t)>;

// Subquestion (a)
template <typename T>
void print(const FunctionType<T>& f, T t)
{
	std::cout << f(t) << '\n';
}

// free function for Subquestion (b) 
double square(const double& x) {
	return pow(x,2);
}

// function object for Subquestion (b)
class expo {
public:
	double operator()(double x) {
		return exp(x);
	}
};

int main()
{
	// Subquestion (b) 
	// assigning f to free function
	FunctionType<double> f = square;
	double x = 4.5;
	cout << x << " squared: ";
	print(f,x);

	// assigning f to stored lambda function
	auto cube = [&](double x) -> double {return pow(x,3);};
	f = cube;
	cout << x << " cubed: ";
	print(f, x);

	// assigning f to a function object
	expo exp;
	f = exp;
	cout << "e ^ " << x << " :";
	print(f, x);

	return 0;
}

