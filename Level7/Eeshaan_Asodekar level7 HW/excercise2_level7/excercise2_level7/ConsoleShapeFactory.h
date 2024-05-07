#pragma once
#ifndef CONSOLESHAPEFACTORY_HPP
#define CONSOLESHAPEFACTORY_HPP

#include "ShapeFactory.h"
#include <tuple>
#include <memory>

class ConsoleShapeFactory : public ShapeFactory {
public:
    std::shared_ptr<Shape> CreateCircle() const override;

    std::shared_ptr<Shape> CreatePoint() const override;

    std::shared_ptr<Shape> CreateLine() const override;

    // Subquestion (a) 
    // new single method whose return type is a tuple whole elements are the products that we wish to create
    std::tuple<std::shared_ptr<Point>, std::shared_ptr<Line>, std::shared_ptr<Circle>> CreateShapes() const override;
};

#endif // CONSOLESHAPEFACTORY_HPP
