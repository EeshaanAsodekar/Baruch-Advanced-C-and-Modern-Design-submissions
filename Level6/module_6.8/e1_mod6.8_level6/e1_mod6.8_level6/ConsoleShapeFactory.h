#pragma once
#ifndef CONSOLESHAPEFACTORY_HPP
#define CONSOLESHAPEFACTORY_HPP

#include "ShapeFactory.h"

// Subquestion (c)
// Derived class ConsoleShapeFactory
class ConsoleShapeFactory : public ShapeFactory {
public:
    std::shared_ptr<Shape> CreateCircle() const override;

    std::shared_ptr<Shape> CreatePoint() const override;

    std::shared_ptr<Shape> CreateLine() const override;
};

#endif // CONSOLESHAPEFACTORY_HPP
