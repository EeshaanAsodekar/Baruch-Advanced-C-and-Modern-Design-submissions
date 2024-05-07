#pragma once
#ifndef SHAPEFACTORY_HPP
#define SHAPEFACTORY_HPP

#include "Circle.h"
#include "Point.h"
#include "Line.h"
#include <memory>
#include <tuple>

class ShapeFactory {
public:
    virtual ~ShapeFactory() {}

    virtual std::shared_ptr<Shape> CreateCircle() const = 0;
    virtual std::shared_ptr<Shape> CreatePoint() const = 0;
    virtual std::shared_ptr<Shape> CreateLine() const = 0;

    // Subquestion (a)
    // new single method whose return type is a tuple whole elements are the products that we wish to create
    virtual  std::tuple<std::shared_ptr<Point>, std::shared_ptr<Line>, std::shared_ptr<Circle>> CreateShapes() const = 0;
};

#endif // SHAPEFACTORY_HPP
