#include "Line.h"
#include <iostream>

// Default constructor
Line::Line() : m_p1(Point()), m_p2(Point()) {}

// Constructor with points
Line::Line(const Point& pt1s, const Point& pt2s) : m_p1(pt1s), m_p2(pt2s) {}

// Copy constructor
Line::Line(const Line& pt) : m_p1(pt.m_p1), m_p2(pt.m_p2) {}

// Assignment operator
Line& Line::operator=(const Line& pt) {
    if (this == &pt) {
        return *this;
    }
    m_p1 = pt.m_p1;
    m_p2 = pt.m_p2;
    return *this;
}

// Return point 1
Point Line::p1() const {
    return m_p1;
}

// Return point 2
Point Line::p2() const {
    return m_p2;
}

// Set point 1
void Line::p1(const Point& ps) {
    m_p1 = ps;
}

// Set point 2
void Line::p2(const Point& ps) {
    m_p2 = ps;
}

// Virtual destructor
Line::~Line() {
    
}

std::ostream& operator<<(std::ostream& os, const Line& l) {
    os << "Line(Start: " << l.p1() << ", End: " << l.p2() << ")";
    return os;
}