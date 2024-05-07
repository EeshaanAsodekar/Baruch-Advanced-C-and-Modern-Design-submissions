#include "ConsoleShapeFactory.h"
#include <iostream>

std::shared_ptr<Shape> ConsoleShapeFactory::CreateCircle() const {
    double x, y, radius;
    std::cout << "Enter center x coordinate for circle: ";
    std::cin >> x;
    std::cout << "Enter center y coordinate for circle: ";
    std::cin >> y;
    std::cout << "Enter radius of circle: ";
    std::cin >> radius;
    return std::make_shared<Circle>(Point(x, y), radius);
}

std::shared_ptr<Shape> ConsoleShapeFactory::CreatePoint() const {
    double x, y;
    std::cout << "Enter x coordinate for point: ";
    std::cin >> x;
    std::cout << "Enter y coordinate for point: ";
    std::cin >> y;
    return std::make_shared<Point>(x, y);
}

std::shared_ptr<Shape> ConsoleShapeFactory::CreateLine() const {
    std::cout << "Enter start point for the line:" << std::endl;
    auto shapeP1 = CreatePoint();

    auto p1 = std::dynamic_pointer_cast<Point>(shapeP1);
    if (!p1) {
        throw std::runtime_error("Failed to create start point for the line.");
    }

    std::cout << "Enter end point for the line:" << std::endl;
    auto shapeP2 = CreatePoint();

    auto p2 = std::dynamic_pointer_cast<Point>(shapeP2);
    if (!p2) {
        throw std::runtime_error("Failed to create end point for the line.");
    }

    return std::make_shared<Line>(*p1, *p2);
}

// new for module 7.1
std::tuple<std::shared_ptr<Point>, std::shared_ptr<Line>, std::shared_ptr<Circle>> ConsoleShapeFactory::CreateShapes() const {
    auto point = std::dynamic_pointer_cast<Point>(CreatePoint());
    auto line = std::dynamic_pointer_cast<Line>(CreateLine());
    auto circle = std::dynamic_pointer_cast<Circle>(CreateCircle());

    return std::make_tuple(point, line, circle);
}
