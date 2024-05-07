#include <iostream>
#include <type_traits>
#include <vector>

// code from level 6  module 6.1 excercise 2 
#include "Point.h"
#include "Shape.h"
#include "Line.h"
#include "Circle.h"

// code written for this excercise
#include "ShapeFactory.h"
#include "ConsoleShapeFactory.h"

// Subquestion (e) Test program
void test() {
    std::unique_ptr<ShapeFactory> factory = std::make_unique<ConsoleShapeFactory>();

    // Creating shapes
    std::shared_ptr<Shape> shapePoint = factory->CreatePoint();
    std::shared_ptr<Shape> shapeLine = factory->CreateLine();
    std::shared_ptr<Shape> shapeCircle = factory->CreateCircle();

    // Downcasting to appropriate type using dynamic_pointer_cast
    auto point = std::dynamic_pointer_cast<Point>(shapePoint);
    auto line = std::dynamic_pointer_cast<Line>(shapeLine);
    auto circle = std::dynamic_pointer_cast<Circle>(shapeCircle);

    // The created shapes
    if (point != nullptr) {
        std::cout << "Point: " << *point << std::endl;
    }
    if (line != nullptr) {
        std::cout << "Line: " << *line << std::endl;
    }
    if (circle != nullptr) {
        std::cout << "Circle: " << *circle << std::endl;
    }
}

int main() {
    test();
    return 0;
}