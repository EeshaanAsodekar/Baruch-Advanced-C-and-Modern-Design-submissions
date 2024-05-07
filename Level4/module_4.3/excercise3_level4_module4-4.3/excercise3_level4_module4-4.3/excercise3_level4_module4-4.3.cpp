#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

// Subquestion (a)
// user-defined random number generator
struct MyRandom {
    int operator() (int n) {
        return std::rand() / (RAND_MAX / n + 1);
    }
};

int main() {
    // create a large vector of integers
    std::vector<int> v;
    int vecSize = 1000;
    for (int i = 0;i < vecSize;i++) {
        v.push_back(i);
    }

    // Subquestion (a)
    // shuffle using random_shuffle() with rand()
    std::random_shuffle(v.begin(), v.end(), MyRandom());
    std::cout << "Shuffled with rand(): ";
    for (int i : v) std::cout << i << ' ';
    std::cout << '\n';

    // shuffle using random_shuffle() with mt19937
    std::random_device rd;
    std::mt19937 g(rd());
    std::random_shuffle(v.begin(), v.end(), [&](int n){return std::uniform_int_distribution<>(0, n - 1)(g);});
    std::cout << "Shuffled with mt19937: ";
    for (int i : v) std::cout << i << ' ';
    std::cout << '\n';

    // shuffle using random_shuffle() with default_random_engine
    std::default_random_engine e(rd());
    std::random_shuffle(v.begin(), v.end(), [&](int n) { return std::uniform_int_distribution<>(0, n - 1)(e); });
    std::cout << "Shuffled with default_random_engine: ";
    for (int i : v) std::cout << i << ' ';
    std::cout << '\n';

    // shuffle using random_shuffle() with linear_congruential_engine
    std::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647> lce(rd());
    std::random_shuffle(v.begin(), v.end(), [&](int n) { return std::uniform_int_distribution<>(0, n - 1)(lce); });
    std::cout << "Shuffled with linear_congruential_engine: ";
    for (int i : v) std::cout << i << ' ';
    std::cout << '\n';

    // Subquestion (b)
    // shuffle using shuffle() with each of the generators
    std::shuffle(v.begin(), v.end(), g);
    std::cout << "Shuffled with shuffle() and mt19937: ";
    for (int i : v) std::cout << i << ' ';
    std::cout << '\n';

    std::shuffle(v.begin(), v.end(), e);
    std::cout << "Shuffled with shuffle() and default_random_engine: ";
    for (int i : v) std::cout << i << ' ';
    std::cout << '\n';

    std::shuffle(v.begin(), v.end(), lce);
    std::cout << "Shuffled with shuffle() and linear_congruential_engine: ";
    for (int i : v) std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}