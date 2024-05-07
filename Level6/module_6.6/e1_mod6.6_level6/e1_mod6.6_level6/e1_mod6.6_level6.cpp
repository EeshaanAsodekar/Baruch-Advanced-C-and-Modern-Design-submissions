#include <iostream>
#include <cmath>
#include <stdexcept>

class Point;

// Subquestion (a)
class DistanceStrategy {
public:
    virtual double Distance(const Point& p1, const Point& p2) const = 0;
    virtual ~DistanceStrategy() {}
};

class Point {
private:
    double x, y;
    static DistanceStrategy* strategy; // Static variable to hold the common strategy

public:
    Point(double xVal, double yVal) : x(xVal), y(yVal) {}

    double GetX() const { return x; }
    double GetY() const { return y; }

    // Static method to set the distance strategy for all Point instances
    static void SetStrategy(DistanceStrategy* newStrategy) {
        strategy = newStrategy;
    }

    // Method to calculate distance using the static strategy
    double Distance(const Point& other) const {
        if (strategy == nullptr) {
            throw std::runtime_error("Distance strategy not set.");
        }
        return strategy->Distance(*this, other);
    }
};

// Initializing the static member
DistanceStrategy* Point::strategy = nullptr;

// Subquestion (c)
// ExactDistance for exact distance calculation using Pythagorean theorem
class ExactDistance : public DistanceStrategy {
public:
    double Distance(const Point& p1, const Point& p2) const override {
        return std::sqrt((p1.GetX() - p2.GetX()) * (p1.GetX() - p2.GetX()) +
            (p1.GetY() - p2.GetY()) * (p1.GetY() - p2.GetY()));
    }
};

// Subquestion (d)
// ApproxDistance for approximate distance calculation (taxicab)
class ApproxDistance : public DistanceStrategy {
public:
    double Distance(const Point& p1, const Point& p2) const override {
        return std::abs(p1.GetX() - p2.GetX()) + std::abs(p1.GetY() - p2.GetY());
    }
};

int main() {
    ExactDistance exactStrategy;
    ApproxDistance approxStrategy;

    // Setting the common strategy for all Points to ExactDistance
    Point::SetStrategy(&exactStrategy);

    Point p1(1, 1);
    Point p2(2, 2);

    // Using the ExactDistance to calculate distance
    std::cout << "Exact distance: " << p1.Distance(p2) << std::endl;

    // Changing the strategy to ApproxDistance
    Point::SetStrategy(&approxStrategy);

    // Now all Points use the ApproxDistance strategy
    std::cout << "Approximate distance after changing strategy: " << p1.Distance(p2) << std::endl;

    return 0;
}

/*
Advantages of passing the DistanceStrategy as a parameter:
Flexibility: It's possible to change the strategy at runtime without affecting the Point class.
Loose coupling: The Point class does not need to know about the specific implementation of the distance calculation.

Disadvantages:
Increased complexity: The client code must manage the lifetime of the strategy objects.
Potential for misuse: Clients must ensure the correct strategy is set before calling the Distance method, which can lead to runtime errors if the strategy is not set.
*/
