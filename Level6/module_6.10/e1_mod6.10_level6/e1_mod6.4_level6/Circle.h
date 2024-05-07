#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iostream>
#include "Point.h"

class Circle : public Shape {
private:
    Point m_center; // Center of the circle
    double m_radius; // Radius of the circle

public:
    // Constructors
    Circle();                                      // Default constructor
    Circle(const Point& c, double r);              // Constructor with center point and radius
    Circle(const Circle& pt);                      // Copy constructor

    // Assignment operator
    Circle& operator=(const Circle& pt);

    // Accessor methods
    Point CenterPoint() const;                     // Return center point
    double Radius() const;                         // Return radius

    // Modifier methods
    void CenterPoint(const Point& centre);         // Set center point
    void Radius(double radius);                    // Set radius

    // Destructor
    virtual ~Circle();                             // Virtual destructor

    friend std::ostream& operator<<(std::ostream& os, const Circle& c);

    std::ostream& print(std::ostream& os) const override {
        os << "Circle(Center: " << m_center << ", Radius: " << m_radius << ")";
        return os;
    }

    Shape* Clone() const override {
        return new Circle(*this);
    }

    // Subquestion (c) mod 6.10
    void Accept(ShapeVisitor& sv);
};

#endif // CIRCLE_HPP
