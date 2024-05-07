// Interface contract specification
#include <concepts>
#include <iostream>

template<typename T, typename Data>
concept IDiffusion = requires (T c, Data t, Data x)
{
    c.diffusion(t, x);
};

template<typename T, typename Data>
concept IDrift = requires (T c, Data t, Data x)
{
    c.drift(t, x);
};

template<typename T, typename Data>
concept IDriftDiffusion = IDiffusion<T, Data>&& IDrift<T, Data>;

template <typename T, typename Data> requires IDriftDiffusion<T, Data>
class SDEAbstract
{ // System under discussion, using composition

// Really a Bridge pattern
private:
    T _t;

public:
    SDEAbstract(const T& t) : _t(t) {}
    Data diffusion(Data t, Data x)
    {
        return _t.diffusion(t, x);
    }

    Data drift(Data t, Data x)
    {
        return _t.drift(t, x);
    }
};

// The new models:
// (1) Implementation for GBM
struct GBMModel {
    double r;
    double D;
    double sigma;

    double drift(double t, double S) const {
        return (r - D) * S;
    }

    double diffusion(double t, double S) const {
        return sigma * S;
    }
};

// (2) GBM with Poisson jumps
struct GBMWithPoisson {
    double r, D, sigma, lambda, jump_amplitude;

    double drift(double t, double S) const {
        return (r - D - lambda * jump_amplitude) * S;
    }

    double diffusion(double t, double S) const {
        return sigma * S;
    }
};

// (3)  PDEs which have convection and diffusion
struct PDEModel {
    double convection_coeff, diffusion_coeff, reaction_coeff;

    double drift(double t, double S) const {
        return convection_coeff * S;
    }

    double diffusion(double t, double S) const {
        return diffusion_coeff * std::pow(S, 2);
    }
};

// some issue in this implementation
//// Modeling Multifactor SDEs
//template<typename... Factors>
//class MultifactorModel {
//public:
//    std::tuple<Factors...> factors;
//
//    // combining multiple factors
//    double drift(double t, double S) {
//        // combining drifts from multiple factors
//        return std::apply([t, S](auto&... factor) {
//            return (factor.drift(t, S) + ...);
//            }, factors);
//    }
//
//    double diffusion(double t, double S) {
//        // combining diffusions from multiple factors
//        return std::apply([t, S](auto&... factor) {
//            return (factor.diffusion(t, S) + ...);
//            }, factors);
//    }
//};