#pragma once
#ifndef SHAPEFACTORY_HPP
#define SHAPEFACTORY_HPP

#include "Circle.h"
#include "Point.h"
#include "Line.h"
#include <memory>

// Subquestion (a)
// Abstract base class ShapeFactory
class ShapeFactory {
public:
    virtual ~ShapeFactory() {}

    // Subquestion (b)
    // Pure virtual member functions for creating shapes
    virtual std::shared_ptr<Shape> CreateCircle() const = 0;
    virtual std::shared_ptr<Shape> CreatePoint() const = 0;
    virtual std::shared_ptr<Shape> CreateLine() const = 0;
};

#endif // SHAPEFACTORY_HPP
