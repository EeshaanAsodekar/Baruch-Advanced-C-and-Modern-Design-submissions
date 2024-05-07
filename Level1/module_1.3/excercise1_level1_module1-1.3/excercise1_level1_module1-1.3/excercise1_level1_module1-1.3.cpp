#include <iostream>
#include <bitset>
#include <vector>

// template variadic function
template <typename T, typename... Types>
void print_variadic(const T& arg, const Types&... args);

// termination/tail function
template <typename T>
void print_variadic(const T& arg);

using namespace std;

// since std::vector class in C++ does not have the standard ouput stream operator << overloaded by default
// I am writing code to overload it, such that the print_variadic template variadic function
// works with it
template <typename t>
ostream& operator<<(ostream& os, const vector<t>& vec) {
    os << "{";
    for (auto itr = vec.begin(); itr != vec.end(); itr++) {
        os << " " << *itr ;
    }
    os << " }";
    return os;
}



int main()
{
    int j = 1; double d = 2.0;
    
    cout << "1 parameter as i/p to print_variadic" << endl;
    print_variadic(j); 
    print_variadic(d); 
    cout << endl;
    cout << "2 parameters as i/p to print_variadic" << endl;
    print_variadic(j, d); 
    print_variadic(d, j);
    cout << endl;
    
    cout << "3 parameters as i/p to print_variadic" << endl;
    print_variadic(d, j, bitset<8>(233));
    print_variadic(d, j, vector<int>{ 99,88,77 });

    return 0;
}

// Subquestion (a)
template <typename T, typename... Types>
void print_variadic(const T& arg, const Types&... args)
{
    cout << arg << ", ";
    print_variadic(args...);
}

template <typename T>
void print_variadic(const T& arg)
{
    cout << arg << endl;
}