#include "UniversalShapeFactory.h"

UniversalShapeFactory::UniversalShapeFactory() {
    // Default factory methods using lambda expressions
    createPoint = []() -> std::shared_ptr<Point> {
        return std::make_shared<Point>(0.0, 0.0);  // Default point
        };

    createLine = []() -> std::shared_ptr<Line> {
        auto start = std::make_shared<Point>(0.0, 0.0);
        auto end = std::make_shared<Point>(1.0, 1.0);
        return std::make_shared<Line>(*start, *end);  // Default line
        };

    createCircle = []() -> std::shared_ptr<Circle> {
        auto center = std::make_shared<Point>(0.0, 0.0);
        return std::make_shared<Circle>(*center, 10.0);  // Default circle
        };
}
