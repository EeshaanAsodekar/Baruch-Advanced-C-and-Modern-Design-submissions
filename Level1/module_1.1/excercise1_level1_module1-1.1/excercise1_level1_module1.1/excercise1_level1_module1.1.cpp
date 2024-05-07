/*
	student: Eeshaan Asodekar
	email: epa6822@nyu.edu
	phone number: +1 347 881 5332
	
	submission for >> 1.1 Lambda Functions >> Exercise 1: First Encounters with Lambda Functions
*/

#include <iostream>
#include <algorithm>
#include <array>
#include <utility>
using namespace std;

int main() {
	cout << "Subquestion (a) and (b):\n\n";
	// defining an stl array of 5 doubles
	array<double, 5> arr{ {1.2,3.6,7.8,-99.7,91.8} };

	cout << "printing arr before transform:" << endl;
	for (auto itr = arr.begin();itr != arr.end();itr++) {
		cout << *itr << "\t";
	}
	cout << endl;

	// Subquestion (a)

	// we are multiplying each element of arr with the number
	double multiply_arrby = 5.5;
	

	// defining a lambda fucntion to  multiply each element of the arr by some factor
	// using the lambda funtion to arr
	// capturing the multuply_arrby multiplication factor by value
	transform(arr.begin(), arr.end(), arr.begin(), [multiply_arrby](double x)->double {
		return x * multiply_arrby;
		});
	
	// to expirment with the multuply_arrby being captured by reference
	array<double, 5> arr2{ {1.2,3.6,7.8,-99.7,91.8} };
	cout << "printing arr2 before transform:" << endl;
	for (auto itr = arr2.begin();itr != arr2.end();itr++) {
		cout << *itr << "\t";
	}

	cout << "\nmultiplication factor: " << multiply_arrby << "\n\n";

	// a lambda fucntion to operate on arr2; multiply each element by a factor
	// capturing the local variable multuply_arrby by reference
	transform(arr2.begin(), arr2.end(), arr2.begin(), [&multiply_arrby](double x)->double {
		return x * multiply_arrby;
		});


	// Subquestion (b)

	cout << "printing arr after transform (multiply_arrby copy-by-value):" << endl;
	for (auto itr = arr.begin();itr != arr.end();itr++) {
		cout << *itr << "\t";
	}
	cout << endl;

	cout << "printing arr2 after transform (multiply_arrby passed by reference):" << endl;
	for (auto itr = arr2.begin();itr != arr2.end();itr++) {
		cout << *itr << "\t";
	}
	cout << endl;

	/*
	* we can see that passing the multiply_arrby captured variable by value or by reference does not make a difference in this case
	* it is because multiply_arrby is not being accumulated/modified in this lambda function
	* threfore arr and arr2 will hold the same result
	*/

	cout << "\n\nSubquestion (c) and (d):\n";

	// Subquestion (c)
	// customLambdaMethod is the custom designed lambda function according to the given requirements
	auto customLambdaMethod = [arr]()->pair<double, double> {
		pair<double, double> minmax;
		minmax.first = arr[0];
		minmax.second = arr[0];

		for_each(arr.begin(), arr.end(), [&minmax](double x) {
			if (x < minmax.first) minmax.first = x;
			if (x > minmax.second) minmax.second = x;
			}
		);
		return minmax;
		};

	auto minmax_customLambdaMethod = customLambdaMethod();
	// Subquestion (d)
	// minmax_minmax_element is the pair holding the o/p of the  std::minmax_element()
	auto minmax_minmax_element = minmax_element(arr.begin(), arr.end());

	cout << endl;

	cout << "lambda fucntion min: " << minmax_customLambdaMethod.first << "\t\tminmax_element() min: " << *minmax_minmax_element.first << "\n\n";

	cout << "lambda fucntion min: " << minmax_customLambdaMethod.second << "\t\tminmax_element() max: " << *minmax_minmax_element.second << "\n\n";

	/*
	* answers to Subquestion (d):
	* yes, our custom designed lambda fucntion in (c) gives the same output as the std::minmax_element
	* also, the customLambdaMethod is easier to read and understand instead of a individual fucntion defined outside of the main
	* since we have storing the Lambda fucntion, it can be easily reused in the code later on if needed
	*/

	return 0;
}

/*
Output obtained:
 
Subquestion (a) and (b):

printing arr before transfrom:
1.2     3.6     7.8     -99.7   91.8
printing arr2 before transfrom:
1.2     3.6     7.8     -99.7   91.8
multiplication factor: 5.5

printing arr after transform (multiply_arrby copy-by-value):
6.6     19.8    42.9    -548.35 504.9
printing arr2 after transform (multiply_arrby passed by reference):
6.6     19.8    42.9    -548.35 504.9


Subquestion (c) and (d):

lambda fucntion min: -548.35        minmax_element() min: -548.35

lambda fucntion min: 504.9          minmax_element() max: 504.9
*/