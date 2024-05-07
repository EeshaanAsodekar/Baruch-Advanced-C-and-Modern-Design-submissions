#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iostream>
#include "ShapeVisitor.h"

class Shape {
public:
    // Constructors
    Shape();                                // Default constructor
    Shape(const Shape& shp);                // Copy constructor

    // Assignment operator
    Shape& operator=(const Shape& shp);

    // making the class pure virtual
    virtual ~Shape() = 0;

    // printing 
    virtual std::ostream& print(std::ostream& os) const = 0;  // Pure virtual print function

    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {
        return shape.print(os);  // Delegate the operation to the virtual function
    }

    virtual Shape* Clone() const = 0;

    //Subquestion (c) - mod 6.10
    virtual void Accept(ShapeVisitor& v) = 0;
};

#endif // SHAPE_HPP


