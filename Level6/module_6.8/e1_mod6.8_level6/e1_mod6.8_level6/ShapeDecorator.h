#pragma once
#ifndef SHAPEDECORATOR_HPP
#define SHAPEDECORATOR_HPP

#include "Shape.h"
#include <iostream>
#include <memory>

// Subquestion (a): Abstract class ShapeDecorator that derives from Shape
class ShapeDecorator : public Shape {
private:
    // Subquestion (b): Holding the shape to decorate
    std::shared_ptr<Shape> decoratedShape;

public:
    // Subquestion (c): Default constructor that sets the shape data-member to ‘null’
    ShapeDecorator() : decoratedShape(nullptr) {}

    // Subquestion (d): Constructor that has a Shape* as an argument
    ShapeDecorator(std::shared_ptr<Shape> shape) : decoratedShape(shape) {}

    // Subquestion (e): Method to return the decorated shape
    std::shared_ptr<Shape> GetShape() const {
        return decoratedShape;
    }

    // Subquestion (e): Method to set the decorated shape
    void SetShape(Shape* shape) {
        decoratedShape = std::shared_ptr<Shape>(shape);
    }

    virtual ~ShapeDecorator() override {}

    // Pure virtual print function to be implemented by the child classes
    virtual std::ostream& print(std::ostream& os) const override = 0;
};

#endif // SHAPEDECORATOR_HPP

