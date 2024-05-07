/*
Structure of code: 
- a struct OptionData to hold the data for an option
- a class SDE that models Geometric Brownian Motion (GBM)
- a main() method (call it the client) that contains the actual algorithm
- SDEAbstract and model classes (in SDEAbstract.h)

motivation of excercise: we wish to postpone implementation details and specific decisions 
for as long as possible with a view to creating highly generic and flexible software
*/

/*
Question: Identify those features in SDE that reduce the flexibility of the code
Answer:
- Hardcoded Computations: The drift and diffusion computations are hardcoded within the SDE class,
tying it exclusively to GBM models and limiting flexibility.
- Tight Coupling: The current class structure couples the option data directly to the SDE computations.
*/

#include <iostream>
#include "StopWatch.cpp" // custom designed; could not find code from excercise
#include "OptionData.h" // custom designed; could not find code from excercise
#include "SDE.h" // moved the given SDE class from main file
#include "SDEAbstract.h" // deliverable for this excercise ... GBM; GBMPoission, PDE, MultifactorModel
#include <random>
#include <memory>
#include <cmath>
#include <iostream>

// fucntion to test the new GBM model with SDEAbstract; inspired from given testing code
void testing_GBM() {
    OptionData myOption{ 65.0, 0.25, 0.08, 0.3, 0.0, -1 };

    GBMModel gbmModel{ myOption.r, myOption.D, myOption.sig };
    SDEAbstract<GBMModel, double> sde(gbmModel);

    double S_0 = 60;
    double VOld = S_0;
    double VNew;
    long NT = 100;
    std::cout << "Number of time steps: ";
    std::cin >> NT;

    long NSIM = 50000;
    std::cout << "Number of simulations: ";
    std::cin >> NSIM;

    double dt = myOption.T / static_cast<double>(NT);
    double sqrdt = std::sqrt(dt);

    double M = static_cast<double>(NSIM);

    double dW;

    double price = 0.0;

    double payoffT;

    double avgPayoffT = 0.0;

    double squaredPayoff = 0.0;

    double sumPriceT = 0.0;

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    StopWatch sw;
    sw.Start();

    for (long i = 1; i <= NSIM; ++i) {
        VOld = S_0;
        double x = 0.0;

        for (long index = 0; index < NT; ++index) {
            double dW = distribution(generator);
            VNew = VOld + (dt * sde.drift(x, VOld)) + (sqrdt * sde.diffusion(x, VOld) * dW);
            VOld = VNew;
            x += dt;
        }

        double payoff = std::max(VNew - myOption.K, 0.0);
        std::cout << "Simulation " << i << ": Payoff " << payoff << std::endl;

        payoffT = myOption.myPayOffFunction(VNew);
        sumPriceT += payoffT;
        avgPayoffT += payoffT / M;
        avgPayoffT *= avgPayoffT;
        squaredPayoff += (payoffT * payoffT);
    }

    price = std::exp(-myOption.r * myOption.T) * sumPriceT / M;

    std::cout << "Price, after discounting: " << price << ", " << std::endl;

    double SD = std::sqrt((squaredPayoff / M) - sumPriceT * sumPriceT / (M * M));

    std::cout << "Standard Deviation: " << SD << ", " << std::endl;

    double SE = SD / std::sqrt(M);

    std::cout << "Standard Error: " << SE << ", " << std::endl;

    sw.Stop();

    std::cout << "Elapsed time in seconds: " << sw.GetTime() << '\n';

}

// fucntion to test the new GBM with Poission model
void testing_GBMWithPoisson() {
    OptionData myOption{ 65.0, 0.25, 0.08, 0.3, 0.0, -1 };  // Example Option Data

    // GBM with Poisson jumps model parameters
    GBMWithPoisson gbmPoissonModel{ myOption.r, myOption.D, myOption.sig, 0.1 /* lambda */, 0.05 /* jump amplitude */ };
    SDEAbstract<GBMWithPoisson, double> sde(gbmPoissonModel);

    double S_0 = 60;
    double VOld = S_0;
    double VNew;
    long NT = 100;
    std::cout << "Number of time steps: ";
    std::cin >> NT;

    long NSIM = 50000;
    std::cout << "Number of simulations: ";
    std::cin >> NSIM;

    double dt = myOption.T / static_cast<double>(NT);
    double sqrdt = std::sqrt(dt);

    double M = static_cast<double>(NSIM);

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);
    std::poisson_distribution<int> poissonDist(gbmPoissonModel.lambda * dt);

    double sumPriceT = 0.0;
    double sumPayoffSquared = 0.0;

    StopWatch sw;
    sw.Start();

    for (long i = 1; i <= NSIM; ++i) {
        VOld = S_0;
        double x = 0.0;

        for (long index = 0; index < NT; ++index) {
            double dW = distribution(generator);
            int jump = poissonDist(generator);
            double jumpComponent = jump * gbmPoissonModel.jump_amplitude;

            VNew = VOld + (dt * sde.drift(x, VOld)) + (sqrdt * sde.diffusion(x, VOld) * dW) + VOld * jumpComponent;
            VOld = VNew;
            x += dt;
        }

        double payoff = std::max(VNew - myOption.K, 0.0);
        sumPriceT += payoff;
        sumPayoffSquared += payoff * payoff;
    }

    sw.Stop();

    double price = std::exp(-myOption.r * myOption.T) * sumPriceT / M;
    std::cout << "Price, after discounting: " << price << ", " << std::endl;

    double SD = std::sqrt((sumPayoffSquared / M) - (sumPriceT / M) * (sumPriceT / M));
    std::cout << "Standard Deviation: " << SD << ", " << std::endl;

    double SE = SD / std::sqrt(M);
    std::cout << "Standard Error: " << SE << ", " << std::endl;

    std::cout << "Elapsed time in seconds: " << sw.GetTime() << '\n';
}

// fucntion to test the new PDE model
void testing_PDEModel() {
    OptionData myOption{ 65.0, 0.25, 0.08, 0.3, 0.0, -1 };

    // PDE model parameters
    PDEModel pdeModel{ 0.05 /* convection_coeff */, 0.02 /* diffusion_coeff */, 0.01 /* reaction_coeff */ };
    SDEAbstract<PDEModel, double> sde(pdeModel);

    double S_0 = 60;
    double VOld = S_0;
    double VNew;
    long NT = 100;
    std::cout << "Number of time steps: ";
    std::cin >> NT;

    long NSIM = 50000;
    std::cout << "Number of simulations: ";
    std::cin >> NSIM;

    double dt = myOption.T / static_cast<double>(NT);
    double sqrdt = std::sqrt(dt);

    double M = static_cast<double>(NSIM);

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    double sumPriceT = 0.0;
    double sumPayoffSquared = 0.0;

    StopWatch sw;
    sw.Start();

    for (long i = 1; i <= NSIM; ++i) {
        VOld = S_0;
        double x = 0.0;

        for (long index = 0; index < NT; ++index) {
            double dW = distribution(generator);
            VNew = VOld + (dt * sde.drift(x, VOld)) + (sqrdt * sde.diffusion(x, VOld) * dW);
            VOld = VNew;
            x += dt;
        }

        double payoff = std::max(VNew - myOption.K, 0.0);
        sumPriceT += payoff;
        sumPayoffSquared += payoff * payoff;
    }

    sw.Stop();

    double price = std::exp(-myOption.r * myOption.T) * sumPriceT / M;
    std::cout << "Price, after discounting: " << price << ", " << std::endl;

    double SD = std::sqrt((sumPayoffSquared / M) - (sumPriceT / M) * (sumPriceT / M));
    std::cout << "Standard Deviation: " << SD << ", " << std::endl;

    double SE = SD / std::sqrt(M);
    std::cout << "Standard Error: " << SE << ", " << std::endl;

    std::cout << "Elapsed time in seconds: " << sw.GetTime() << '\n';
}

// given testing code
void oldSchoolGBM()
{
    std::cout << "1 factor MC with explicit Euler\n";
    OptionData myOption{ 65.0, 0.25, 0.08, 0.3, 0.0, -1 };

    SDE sde(myOption);

    // Initial value of SDE
    double S_0 = 60;
    // Variables for underlying stock
    double x;
    double VOld = S_0;
    double VNew;
    long NT = 100;

    std::cout << "Number of time steps: ";
    std::cin >> NT;

    // V2 mediator stuff
    long NSIM = 50000;
    std::cout << "Number of simulations: ";
    std::cin >> NSIM;

    double M = static_cast<double>(NSIM);
    double dt = myOption.T / static_cast<double> (NT);
    double sqrdt = std::sqrt(dt);

    // Normal random number

    double dW;

    double price = 0.0; // Option price

    double payoffT;

    double avgPayoffT = 0.0;

    double squaredPayoff = 0.0;

    double sumPriceT = 0.0;

    // #include <random>

    // Normal (0,1) rng

    std::default_random_engine dre;

    std::normal_distribution<double> nor(0.0, 1.0);

    // Create a random number

    dW = nor(dre);

    StopWatch sw;

    sw.Start();


    for (long i = 1; i <= M; ++i)
    {
        // Calculate a path at each iteration
        if ((i / 100'000) * 100'000 == i)
        {
            // Give status after each 10000th iteration
            std::cout << i << ", ";
        }
        VOld = S_0;
        x = 0.0;
        for (long index = 0; index <= NT; ++index)
        {
            // Create a random number
            dW = nor(dre);
            // The FDM (in this case explicit Euler)
            VNew = VOld + (dt * sde.drift(x, VOld)) + (sqrdt * sde.diffusion(x, VOld) * dW);
            VOld = VNew;
            x += dt;
        }

        // Assemble quantities (postprocessing)
        payoffT = myOption.myPayOffFunction(VNew);
        sumPriceT += payoffT;
        avgPayoffT += payoffT / M;
        avgPayoffT *= avgPayoffT;

        squaredPayoff += (payoffT * payoffT);
    }

    // Finally, discounting the average price
    price = std::exp(-myOption.r * myOption.T) * sumPriceT / M;
    std::cout << "Price, after discounting: " << price << ", " << std::endl;

    double SD = std::sqrt((squaredPayoff / M) - sumPriceT * sumPriceT / (M * M));
    std::cout << "Standard Deviation: " << SD << ", " << std::endl;

    double SE = SD / std::sqrt(M);
    std::cout << "Standard Error: " << SE << ", " << std::endl;

    sw.Stop();
    std::cout << "Elapsed time in seconds: " << sw.GetTime() << '\n';
}

int main() {
    oldSchoolGBM();
    testing_GBM();
    testing_GBMWithPoisson();
    testing_PDEModel();

    return 0;
}