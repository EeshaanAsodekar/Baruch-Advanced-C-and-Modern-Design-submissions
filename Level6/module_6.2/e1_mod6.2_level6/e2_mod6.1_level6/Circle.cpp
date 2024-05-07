#include "Circle.h"
#include <iostream>

// Default constructor
Circle::Circle() : m_center(Point()), m_radius(1.0) {} // Default to radius 1.0

// Constructor with center point and radius
Circle::Circle(const Point& c, double r) : m_center(c), m_radius(r) {}

// Copy constructor
Circle::Circle(const Circle& pt) : m_center(pt.m_center), m_radius(pt.m_radius) {}

// Assignment operator
Circle& Circle::operator=(const Circle& pt) {
    if (this == &pt) {
        return *this;
    }
    m_center = pt.m_center;
    m_radius = pt.m_radius;
    return *this;
}

// Return center point
Point Circle::CenterPoint() const {
    return m_center;
}

// Return radius
double Circle::Radius() const {
    return m_radius;
}

// Set center point
void Circle::CenterPoint(const Point& centre) {
    m_center = centre;
}

// Set radius
void Circle::Radius(double radius) {
    m_radius = radius;
}

// Virtual destructor
Circle::~Circle() {

}

std::ostream& operator<<(std::ostream& os, const Circle& c) {
    os << "Circle(Center: " << c.m_center << ", Radius: " << c.m_radius << ")";
    return os;
}