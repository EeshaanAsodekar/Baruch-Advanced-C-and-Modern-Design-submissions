#include <iostream>
#include <cmath>
#include <stdexcept>

class Point;

class DistanceStrategy {
public:
    virtual double Distance(const Point& p1, const Point& p2) const = 0;
    virtual ~DistanceStrategy() {}
};

class Point {
private:
    double x, y;

public:
    Point(double xVal, double yVal) : x(xVal), y(yVal) {}

    double GetX() const { return x; }
    double GetY() const { return y; }

    // New method to calculate distance using the given strategy object
    double Distance(const Point& other, const DistanceStrategy& strategy) const {
        return strategy.Distance(*this, other);
    }
};

class ExactDistance : public DistanceStrategy {
public:
    double Distance(const Point& p1, const Point& p2) const override {
        return std::sqrt((p1.GetX() - p2.GetX()) * (p1.GetX() - p2.GetX()) +
            (p1.GetY() - p2.GetY()) * (p1.GetY() - p2.GetY()));
    }
};

class ApproxDistance : public DistanceStrategy {
public:
    double Distance(const Point& p1, const Point& p2) const override {
        return std::abs(p1.GetX() - p2.GetX()) + std::abs(p1.GetY() - p2.GetY());
    }
};

int main() {
    ExactDistance exactStrategy;
    ApproxDistance approxStrategy;

    Point p1(1, 1);
    Point p2(2, 2);

    // Using the ExactDistance strategy by passing it as a parameter
    std::cout << "Exact distance: " << p1.Distance(p2, exactStrategy) << std::endl;

    // Using the ApproxDistance strategy by passing it as a parameter
    std::cout << "Approximate distance: " << p1.Distance(p2, approxStrategy) << std::endl;

    return 0;
}

/*
Static Data Member
Advantages:
- Set the strategy once for all Point instances.
- Uniform strategy use all across.

Disadvantages:
- Changes affect all instances, reducing adaptability.
- Potential race conditions in multi-threaded scenarios.

Passing Strategy as an Argument
Advantages:
- Allows using different strategies on a per-call basis.
- Decoupling

Disadvantages:
- Requires explicitly passing the strategy for every distance calculation.
*/
