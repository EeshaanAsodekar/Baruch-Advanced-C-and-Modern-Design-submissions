#pragma once
#include <vector>
#include <iostream>
using namespace std;
class C
{
private:
	// excercise question does not specify what is the required data type of std::vector
	// I am using a vector of int
	// also, I could have alternatively converted C into a template class; and have had used vector<Type> as the data member
	vector<int> vec;

	// copy constructor
	explicit C(const C& Cobj) = delete;

	// assignment operator
	C& operator=(const C& Cobj) = delete;

public:
	// using the 'default' keyword to ensure that the compiler to define the function only if needed
	// default constructor
	explicit C() = default;

	// constructor with parameters
	explicit C(const vector<int> vec_): vec(vec_) {};

	//// copy constructor
	//C(const C& Cobj) : vec(Cobj.vec) { cout << "\nfrom C's copy constructor" << endl; };

	//// assignment operator
	//C& operator=(const C& Cobj);

	// destructor
	~C();

	// print the contents of the vector<int> vec data member
	void print() noexcept;

	// double the values of the vector<int> vec data member
	void scale_to_double() noexcept;

	// in the print() and the scale_to_double() member functions, the 'noexcept' keyword helps us to 
	// ensure that these member functions cannot throw an exception; as specficied in the excercise requirments

	// to be able to modify the vec data member of the C class
	void modify_vec(const vector<int>& vec_) { vec = vec_; }

	constexpr void modify_vec(const int arr[], const int& size) {
		for (int i = 0;i < size;i++) vec.push_back(arr[i]);
	}
};

