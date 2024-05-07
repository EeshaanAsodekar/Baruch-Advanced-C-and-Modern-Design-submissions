#include <random>
#include <iostream>

int main() {
    // Subquestion (a): Create a random number engine and set its seed (for example, using std::random_device)
    std::random_device rd;
    std::mt19937 gen(rd());

    // Subquestion (b): Create two instances of std::uniform_real_distribution<double> on the unit interval
    std::uniform_real_distribution<> udis(0, 1);
    std::uniform_real_distribution<> udis_(0, 1);

    int trials = 0;
    int hits = 0;
    double pi_estimate = 0.0;
    
    // Subquestion (c): create a loop  
    while (std::abs(pi_estimate - 3.14159) >= 0.00001) {
        // generate uniform random values x and y
        double x = udis(gen);
        double y = udis_(gen);

        // distance^2
        if (x * x + y * y <= 1.0) {
            hits++;
        }

        trials++;
        pi_estimate = 4.0 * hits / trials;
    }

    // Subquestion (d)
    std::cout << "After " << trials << " trials, the estimated value of pi is " << pi_estimate << std::endl;

    return 0;
}
