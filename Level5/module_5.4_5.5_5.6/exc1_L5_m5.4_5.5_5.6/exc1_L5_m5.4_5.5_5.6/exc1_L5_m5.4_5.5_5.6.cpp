#include <iostream>
#include <functional>
#include <boost/functional/hash.hpp>
#include <string>
#include <limits>

// Subquestion (a) create two generic functions to hash arbitrary data types using Boost and C++11.
// using Boost
template <typename T>
std::size_t hashWithBoost(const T& key) {
    boost::hash<T> hasher;
    return hasher(key);
}

// using C++11
template <typename T>
std::size_t hashWithCpp11(const T& key) {
    std::hash<T> hasher;
    return hasher(key);
}

int main() {
    // Subquestion (b) test the functions using integers, strings, pointers, std::numeric_limits<long>::max().
    int integer = 10;
    std::string str = "Hello, World!";
    int* ptr = &integer;
    long maxLong = std::numeric_limits<long>::max();

    std::cout << "Boost hash of integer: " << hashWithBoost(integer) << std::endl;
    std::cout << "C++11 hash of integer: " << hashWithCpp11(integer) << std::endl;

    std::cout << "Boost hash of string: " << hashWithBoost(str) << std::endl;
    std::cout << "C++11 hash of string: " << hashWithCpp11(str) << std::endl;

    std::cout << "Boost hash of pointer: " << hashWithBoost(ptr) << std::endl;
    std::cout << "C++11 hash of pointer: " << hashWithCpp11(ptr) << std::endl;

    std::cout << "Boost hash of max long: " << hashWithBoost(maxLong) << std::endl;
    std::cout << "C++11 hash of max long: " << hashWithCpp11(maxLong) << std::endl;

    // Subquestion (c) create two hashes h1 and h2 of two strings and then compute h1 ^ (h2 << 1).
    std::size_t h1 = hashWithBoost(std::string("string1"));
    std::size_t h2 = hashWithBoost(std::string("string2"));
    std::size_t result = h1 ^ (h2 << 1);

    std::cout << "Result of hashWithBoost(\"string1\") " << h1 << std::endl;
    std::cout << "Result of hashWithBoost(\"string2\") " << h2 << std::endl;
    std::cout << "Result of h1 ^ (h2 << 1): " << result << std::endl;

    return 0;
}
