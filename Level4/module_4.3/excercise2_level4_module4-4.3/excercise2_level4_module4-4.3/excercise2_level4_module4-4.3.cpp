#include <iostream>
#include <random>
#include <map>

// Subquestion (a): generic function to generate a list of random numbers for a generic engine and a generic distribution
template <typename Dist, typename Eng>
void GenerateRandomNumbers(Dist d, Eng eng, int NTrials, const std::string& s) {
    std::map<long long, int> counter;

    // appending the value on the map
    for (int i = 0; i < NTrials; ++i) {
        ++counter[d(eng)];
    }

    // printing a vertical histogram to visualize the variates of the distribution
    std::cout << s << " distribution:\n";
    for (const auto& p : counter) {
        std::cout << p.first << ": ";
        for (int i = 0; i < p.second; ++i) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    std::default_random_engine eng;
    int NTrials = 200;

    // Subquestion (b) Test the code by choosing the distributions: geometric, uniform and poisson.
    std::geometric_distribution<> geometric_dist(0.5);
    GenerateRandomNumbers(geometric_dist, eng, NTrials, "Geometric");

    std::uniform_int_distribution<> uniform_dist(0, 10);
    GenerateRandomNumbers(uniform_dist, eng, NTrials, "Uniform");

    std::poisson_distribution<> poisson_dist(2.0);
    GenerateRandomNumbers(poisson_dist, eng, NTrials, "Poisson");

    // Subquestion (c)
    // Yes, the histograms generated do look like the probability of these disbtrutions
    // we can see that the geometric has the highest frequency closest to 0, which goes on exponentially falling
    // the uniform distribution histogram seems to well balanced between 0 and 10
    // and we see the early increase, a peaking and the decrease in the histogram of the poission
    // thus, all 3 distribution histograms look like the probability of the distribs.

    return 0;
}
