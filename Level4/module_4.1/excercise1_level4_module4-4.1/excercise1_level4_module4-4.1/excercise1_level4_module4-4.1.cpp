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
        std::cout << data << std::endl;
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


int main()
{
    Proposition x(1);
    Proposition y(0);
    Proposition z(0);

    // Subquestion (c)
    std::cout << "Subquestion (c)\n"; // satisfies De Morgan’s Laws
    std::cout << "checking if Proposition follows De Morgans laws:\n";
    // checking NOT (A OR B) == NOT(A) AND NOT(B)
    !(x | y) == (!(x) & !(y)) ? std::cout << "Proposition satisfies De Morgans Laws\n":
        std::cout << "Proposition does not satisfy De Morgan’s Laws\n";

    // checking NOT (A AND B) == NOT(A) OR NOT(B)
    !(x & y) == (!(x) | !(y)) ? std::cout << "Proposition satisfies De Morgans Laws\n" :
        std::cout << "Proposition does not satisfy De Morgan’s Laws\n";


    // Subquestion (d)
    std::cout << "\nSubquestion (d)\n"; //  satisfies the Distributive Laws
    std::cout << "checking if Proposition follows Distributive Laws:\n";
    //  A AND (B OR C) = (A AND B) OR (A AND C)
    (x & (y | z)) == ((x & y) | (x & z)) ? std::cout << "Proposition satisfies Distributive Laws\n" :
        std::cout << "Proposition does not satisfy Distributive Laws\n";

    // checking A OR(B AND C) == (A OR B) AND (A OR C)
    (x | (y & z)) == ((x | y) & (x | z)) ? std::cout << "Proposition satisfies Distributive Laws\n" :
        std::cout << "Proposition does not satisfy Distributive Laws\n";

    std::cout << "\nSubquestion (e)\n";
    Proposition A, B, C;
    // Subquestion (e)
    // checking all the testcases for the three inputs
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                A = bool(i);
                B = bool(j);
                C = bool(k);

                // [A -> (B -> C)] <-> [(A & B) -> C]
                auto result = ((A % (B % C)) * ((A & B) % C));
                result.print();// all print 1
            }
        }
    }

    return 0;
}

