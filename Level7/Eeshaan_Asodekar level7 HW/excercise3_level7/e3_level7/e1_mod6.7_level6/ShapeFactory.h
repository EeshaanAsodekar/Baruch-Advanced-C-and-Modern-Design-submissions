#pragma once
#ifndef SHAPEFACTORY_HPP
#define SHAPEFACTORY_HPP

#include "Circle.h"
#include "Point.h"
#include "Line.h"
#include "PolylineMod.h"
#include <memory>

class ShapeFactory {
public:
    virtual ~ShapeFactory() {}

    virtual std::shared_ptr<Shape> CreateCircle() const = 0;
    virtual std::shared_ptr<Shape> CreatePoint() const = 0;
    virtual std::shared_ptr<Shape> CreateLine() const = 0;

    // newly added for e3 lvl 7
    virtual std::shared_ptr<Shape> CreatePolyLine() const = 0;
};

#endif // SHAPEFACTORY_HPP
