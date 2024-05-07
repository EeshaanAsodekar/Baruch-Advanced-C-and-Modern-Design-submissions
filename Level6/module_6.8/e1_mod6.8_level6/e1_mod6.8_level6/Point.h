#pragma once
#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include "Shape.h"

class Point : public Shape {
private:
    double m_x;
    double m_y;

public:
    // Constructors
    Point();                                // Default constructor
    Point(double xs, double ys);            // Constructor with coordinates
    Point(const Point& pt);                 // Copy constructor

    // Assignment operator
    Point& operator=(const Point& pt);

    // Access functions for the coordinates
    double x() const;                       // Return x coordinate
    double y() const;                       // Return y coordinate

    // Modifier functions for the coordinates
    void x(double xs);                      // Set x coordinate
    void y(double ys);                      // Set y coordinate

    // Destructor
    virtual ~Point();                       // Virtual destructor

    friend std::ostream& operator<<(std::ostream& os, const Point& p);


    std::ostream& print(std::ostream& os) const override {
        os << "Point(" << m_x << ", " << m_y << ")";
        return os;
    }

    double Distance(const Point& p) const;

    double Distance() const;

    double Distance();

    // Subquestion (c)
    Shape* Clone() const override {
        return new Point(*this);
    }

};

#endif // POINT_HPP

