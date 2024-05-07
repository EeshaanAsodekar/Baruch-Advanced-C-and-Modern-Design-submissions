#pragma once
#include <vector>
#include <iostream>
using namespace std;
class C
{
private:
	vector<int> vec;

	// copy constructor
	explicit C(const C& Cobj) = delete;

	// assignment operator
	C& operator=(const C& Cobj) = delete;

public:
	// default constructor
	explicit C() = default;

	// constructor with parameters
	explicit C(const vector<int> vec_) : vec(vec_) {};

	// Subquestion (a) - Excercise 3 1-1.2
	// move constructor
	C(C&& source) noexcept {
		vec = move(source.vec);
	}

	// Subquestion (a) - Excercise 3 1-1.2
	// move assignment operator
	C& operator=(C&& source)noexcept {
		vec = move(source.vec);
		return *this;
	}

	// destructor
	~C();

	// print the contents of the vector<int> vec data member
	void print() noexcept;

	// double the values of the vector<int> vec data member
	void scale_to_double() noexcept;

	// to be able to modify the vec data member of the C class
	void modify_vec(const vector<int>& vec_) { vec = vec_; }

	// to modify the vec with a constexpr int array as input
	constexpr void modify_vec(const int arr[], const int& size) {
		for (int i = 0;i < size;i++) vec.push_back(arr[i]);
	}
};

