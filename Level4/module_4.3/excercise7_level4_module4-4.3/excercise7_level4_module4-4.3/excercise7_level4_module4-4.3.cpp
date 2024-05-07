#include <random>
#include <vector>
#include <iostream>
#include <cmath>

// Subquestion (a)
// funcion to compute the chi-squared statistic
double computeChiSquared(const std::vector<int>& observed, int N, double p) {
    double chiSquared = 0.0;
    for (int i = 0; i < observed.size(); ++i) {
        double expected = N * p;
        chiSquared += std::pow(observed[i] - expected, 2) / expected;
    }
    return chiSquared;
}

// function to print a histogram using asterisks
void printHistogram(const std::vector<int>& observed, int scale) {
    for (int i = 0; i < observed.size(); ++i) {
        std::cout << i << ": ";
        int numAsterisks = observed[i] / scale;
        for (int j = 0; j < numAsterisks; ++j) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
}

int main() {
    // Subquestion (c)
    int N = 10000;  // total number of observations
    int k = 10;     // range of integers
    double p = 1.0 / k;  // probability for each integer

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, k - 1);

    std::vector<int> observed(k, 0);
    for (int n = 0; n < N; ++n) {
        ++observed[dis(gen)];
    }

    double chiSquared = computeChiSquared(observed, N, p);
    std::cout << "Chi-squared statistic forobserved vector: " << chiSquared << std::endl;

    std::cout << "\nHistogram: " << std::endl;
    // print the histogram
    int scale = 100;  // for appropriately displaying
    printHistogram(observed, scale);

    return 0;
}
