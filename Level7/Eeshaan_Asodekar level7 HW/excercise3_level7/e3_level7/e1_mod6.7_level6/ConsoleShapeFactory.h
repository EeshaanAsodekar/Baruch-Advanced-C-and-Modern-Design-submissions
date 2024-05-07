#pragma once
#ifndef CONSOLESHAPEFACTORY_HPP
#define CONSOLESHAPEFACTORY_HPP

#include "ShapeFactory.h"

class ConsoleShapeFactory : public ShapeFactory {
public:
    std::shared_ptr<Shape> CreateCircle() const override;

    std::shared_ptr<Shape> CreatePoint() const override;

    std::shared_ptr<Shape> CreateLine() const override;

    // newly added for e3 lvl 7
    std::shared_ptr<Shape> CreatePolyLine() const override;
};

#endif // CONSOLESHAPEFACTORY_HPP
