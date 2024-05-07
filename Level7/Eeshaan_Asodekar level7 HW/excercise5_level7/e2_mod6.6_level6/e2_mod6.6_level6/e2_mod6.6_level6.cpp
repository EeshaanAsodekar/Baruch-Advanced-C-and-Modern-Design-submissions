#include <iostream>
#include <cmath>
#include <functional>
#include <future>

// Forward declaration of Point class needed for DistanceAlgorithm type
class Point;

// Subquestion (a) Creating an interface represented as a function wrapper for distance computation
using DistanceAlgorithm = std::function<double(const Point&, const Point&)>;

// Point class
class Point {
private:
    double x, y;

public:
    Point(double xVal, double yVal) : x(xVal), y(yVal) {}

    double GetX() const { return x; }
    double GetY() const { return y; }

    // Subquestion (b) Modified Point class to use the function wrapper strategy for distance calculation
    double Distance(const Point& other, DistanceAlgorithm algorithm) const {
        return algorithm(*this, other);
    }
};

// Subquestion (b) Stateless strategy implementations as lambda expressions
// Phytagoras algorithm as a lambda (stateless version)
auto phytagoras = [](const Point& p1, const Point& p2) {
    return std::sqrt((p1.GetX() - p2.GetX()) * (p1.GetX() - p2.GetX()) +
        (p1.GetY() - p2.GetY()) * (p1.GetY() - p2.GetY()));
    };

// Taximan algorithm as a lambda (stateless version)
auto taximan = [](const Point& p1, const Point& p2) {
    return std::abs(p1.GetX() - p2.GetX()) + std::abs(p1.GetY() - p2.GetY());
    };

// Subquestion (c) Stateful functor for when the algorithm needs to maintain state between calls
// Stateful functor for Pythagoras algorithm
class PythagorasFunctor {
    static int counter;

public:
    double operator()(const Point& p1, const Point& p2) {
        ++counter;
        std::cout << "\nPythagorasFunctor counter: " << counter << std::endl;
        return std::sqrt((p1.GetX() - p2.GetX()) * (p1.GetX() - p2.GetX()) +
            (p1.GetY() - p2.GetY()) * (p1.GetY() - p2.GetY()));
    }
};

int PythagorasFunctor::counter = 0;

// Stateful functor for Approximate (Taximan) algorithm
class ApproximateFunctor {
    static int counter;

public:
    double operator()(const Point& p1, const Point& p2) {
        ++counter;
        std::cout << "\nApproximateFunctor counter: " << counter << std::endl;
        return std::abs(p1.GetX() - p2.GetX()) + std::abs(p1.GetY() - p2.GetY());
    }
};

int ApproximateFunctor::counter = 0;

int main() {
    Point p1(1, 1);
    Point p2(4, 5);

    // Using the stateless strategies to calculate distances
    std::cout << "Phytagoras distance: " << p1.Distance(p2, phytagoras) << std::endl;
    std::cout << "Taximan distance: " << p1.Distance(p2, taximan) << std::endl;

    // Testing stateful functors
    PythagorasFunctor pythagorasFunctor;
    ApproximateFunctor approximateFunctor;

    // Testing the PythagorasFunctor with state
    std::cout << "Pythagoras distance with state: " << p1.Distance(p2, pythagorasFunctor) << std::endl;
    // Calling again to see the state effect
    std::cout << "Pythagoras distance with state (second call): " << p1.Distance(p2, pythagorasFunctor) << std::endl;

    // Testing the ApproximateFunctor with state
    std::cout << "Approximate distance with state: " << p1.Distance(p2, approximateFunctor) << std::endl;
    // Calling again to see the state effect
    std::cout << "Approximate distance with state (second call): " << p1.Distance(p2, approximateFunctor) << std::endl;

    // Subquestion (d) Implementing the Phytagoras algorithm as a concurrent task using C++11 futures
    auto futurePhytagoras = std::async(std::launch::async, phytagoras, p1, p2);
    std::cout << "Concurrent Phytagoras distance: " << futurePhytagoras.get() << std::endl;

    return 0;
}
