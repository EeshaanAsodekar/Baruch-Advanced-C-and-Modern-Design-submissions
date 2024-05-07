#pragma once
#include <functional>
#include <memory>
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "ConsoleShapeFactory.h"

// Subquestion (a)
class UniversalShapeFactory {
public:
    // Factory methods as std::function
    std::function<std::shared_ptr<Point>()> createPoint;
    std::function<std::shared_ptr<Line>()> createLine;
    std::function<std::shared_ptr<Circle>()> createCircle;

    // Constructor - let us set defaults
    UniversalShapeFactory();
};
