#ifndef LINE_HPP
#define LINE_HPP

#include <iostream>
#include "Point.h"

class Line : public Shape {
private:
    Point m_p1;  // Start point of the line
    Point m_p2;  // End point of the line

public:
    // Constructors
    Line();                                   // Default constructor
    Line(const Point& pt1s, const Point& pt2s);   // Constructor with points
    Line(const Line& pt);                    // Copy constructor

    // Assignment operator
    Line& operator=(const Line& pt);

    // Accessor methods for the points
    Point p1() const;                         // Return point 1
    Point p2() const;                         // Return point 2

    // Modifier methods for the points
    void p1(const Point& ps);                 // Set point 1
    void p2(const Point& ps);                 // Set point 2

    // Destructor
    virtual ~Line();                          // Virtual destructor

    friend std::ostream& operator<<(std::ostream& os, const Line& l);

    std::ostream& print(std::ostream& os) const override {
        os << "Line(Start: " << m_p1 << ", End: " << m_p2 << ")";
        return os;
    }

    double Length() const;

    Shape* Clone() const override {
        return new Line(*this);
    }

    // Subquestion (c) mod 6.10
    void Accept(ShapeVisitor& sv);
};

#endif // LINE_HPP
