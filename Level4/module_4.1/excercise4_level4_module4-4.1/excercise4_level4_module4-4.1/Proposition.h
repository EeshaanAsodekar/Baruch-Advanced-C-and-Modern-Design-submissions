#pragma once
#include <iostream>
#include <bitset>

class Proposition {
private:
	std::bitset<1> data;

public:
	// Subquestion (a)
	// default constructor
	// the default value is 0/false
	Proposition() : data(0) {}

	// constructor with bool as argument
	Proposition(bool b) : data(b) {}

	// constructor with std::bitset<1> as argument
	Proposition(std::bitset<1> b) : data(b) {}

	// utility print fucntion
	void print() {
		std::cout << data;
	}

	// Subquestion (b)
	// overloading Boolean operators - using the boolean operators on std::bitset
	// conjunction
	Proposition operator&(const Proposition& p) {
		return Proposition(data & p.data);
	}

	// disjunction
	Proposition operator|(const Proposition& p) {
		return Proposition(data | p.data);
	}

	// exclusive or
	Proposition operator^(const Proposition& p) {
		return Proposition(data ^ p.data);
	}

	// negation
	Proposition operator!() {
		return Proposition(~data);
	}

	// equality
	bool operator==(const Proposition& p) {
		return data == p.data;
	}

	// inequality
	bool operator!=(const Proposition& p) {
		return data != p.data;
	}

	// overloading assignment operator
	Proposition& operator=(bool b) {
		data = b;
		return *this;
	}

	// friend functions for conditional and biconditional operators
	friend Proposition operator%(const Proposition& p1, const Proposition& p2);
	friend Proposition operator*(const Proposition& p1, const Proposition& p2);
	friend Proposition operator&(const Proposition& p1, const Proposition& p2);
	friend Proposition operator|(const Proposition& p1, const Proposition& p2);
	friend Proposition operator^(const Proposition& p1, const Proposition& p2);


	// cannot have operator<->; not allowed.
	// we are using the operator* to represent the Biconditional operation
};

// implementation of conditional operator
Proposition operator%(const Proposition& p1, const Proposition& p2) {
	return Proposition(~p1.data | p2.data);
}

// implementation of biconditional operator
Proposition operator*(const Proposition& p1, const Proposition& p2) {
	return Proposition(~(p1.data ^ p2.data));
}

// implementation of AND operator
Proposition operator&(const Proposition& p1, const Proposition& p2) {
	return Proposition(p1.data * p2.data);
}

// implementation of OR operator
Proposition operator|(const Proposition& p1, const Proposition& p2) {
	return Proposition(p1.data | p2.data);
}

// implementation of XOR operator
Proposition operator^(const Proposition& p1, const Proposition& p2) {
	return Proposition(p1.data ^ p2.data);
}

