#include <random>
#include <iostream>
#include <sstream>

// Subquestion (a), (b), and (c)
// generic function to generate a list of random numbers for a generic engine and a generic distribution
template <typename Engine, typename Distribution>
void generate_random_numbers(Engine& eng, Distribution& dist, int nTrials) {
    for (int i = 0; i < nTrials; ++i) {
        std::cout << dist(eng) << ", ";
    }
    std::cout << "end of sequence\n\n";
}

int main()
{
    // Given code:
    // Choose the engine
    std::default_random_engine eng;
    // Generate uniform random variates in interval [A, B]
    double A = 0.0;
    double B = 1.0;
    std::uniform_real_distribution<double> dist(A, B);
    int nTrials = 30;

    std::cout << "\nrandom numbers generated using uniform_real_distribution<double> dist(A, B)" << std::endl;
    // Produce a number of uniform variates
    for (int i = 1; i <= nTrials; ++i)
    {
        std::cout << dist(eng) << ", ";
    }
    std::cout << "end\n\n";

    // Subquestion (a)
    // std::linear_congruential_engine<uni, a, c, m> lce
    // a is the multiplier parameter used in the transition algorithm.
    // c is the increment parameter used in the transition algorithm.
    // m is the modulus parameter used in the transition algorithm.
    
    // a) Using std::linear_congruential_engine, std::mt19937, and std::mt19937_64
    std::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647> lce;
    std::mt19937 mte;
    std::mt19937_64 mte64;

    std::cout << "Using linear_congruential_engine:\n";
    generate_random_numbers(lce, dist, nTrials);

    std::cout << "Using mt19937:\n";
    generate_random_numbers(mte, dist, nTrials);

    std::cout << "Using mt19937_64:\n";
    generate_random_numbers(mte64, dist, nTrials);

    // Subquestion (b) and (c): generating different distributions using mte
    std::normal_distribution<double> normal_dist(0.0, 1.0);
    std::chi_squared_distribution<double> chi_squared_dist(2.0);
    std::bernoulli_distribution bernoulli_dist(0.5);
    std::cauchy_distribution<double> cauchy_dist(0.0, 1.0);

    std::cout << "Using normal_distribution:\n";
    generate_random_numbers(mte, normal_dist, nTrials);

    std::cout << "Using chi_squared_distribution:\n";
    generate_random_numbers(mte, chi_squared_dist, nTrials);

    std::cout << "Using bernoulli_distribution:\n";
    generate_random_numbers(mte, bernoulli_dist, nTrials);

    std::cout << "Using cauchy_distribution:\n";
    generate_random_numbers(mte, cauchy_dist, nTrials);

    return 0;
}
