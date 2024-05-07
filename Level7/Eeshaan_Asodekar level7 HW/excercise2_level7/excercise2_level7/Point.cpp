#include "Point.h"
#include <iostream>

// Default constructor
Point::Point() : m_x(0.0), m_y(0.0) {}

// Constructor with coordinates
Point::Point(double xs, double ys) : m_x(xs), m_y(ys) {}

// Copy constructor
Point::Point(const Point& pt) : m_x(pt.m_x), m_y(pt.m_y) {}

// Assignment operator
Point& Point::operator=(const Point& pt) {
    if (this == &pt) {
        return *this;
    }
    m_x = pt.m_x;
    m_y = pt.m_y;
    return *this;
}

// Return x coordinate
double Point::x() const {
    return m_x;
}

// Return y coordinate
double Point::y() const {
    return m_y;
}

// Set x coordinate
void Point::x(double xs) {
    m_x = xs;
}

// Set y coordinate
void Point::y(double ys) {
    m_y = ys;
}

// destructor
Point::~Point() {

}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "Point(" << p.m_x << "," << p.m_y << ")";
    return os;
}

// Subquestion (b)
// Calculate the distance to another point
double Point::Distance(const Point& p) const {
    return sqrt((m_x - p.m_x) * (m_x - p.m_x) + (m_y - p.m_y) * (m_y - p.m_y));
}

// Subquestion (c)
// Calculate the distance to the origin
double Point::Distance() const {
    return sqrt(m_x * m_x + m_y * m_y);
}