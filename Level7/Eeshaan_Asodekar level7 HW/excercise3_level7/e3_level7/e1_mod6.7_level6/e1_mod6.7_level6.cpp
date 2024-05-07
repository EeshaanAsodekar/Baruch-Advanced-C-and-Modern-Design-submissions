#include <iostream>
#include <type_traits>
#include <vector>
#include "Point.h"
#include "Shape.h"
#include "Line.h"
#include "Circle.h"
#include "ShapeFactory.h"
#include "ConsoleShapeFactory.h"
#include "PolylineMod.h"
#include "ShapeComposite.h"

// testing if previous features still work
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

// testing if previous features still work
void test2() {
    // Creating individual shapes using smart pointers
    auto p1 = std::make_shared<Point>(0.0, 0.0);
    auto p2 = std::make_shared<Point>(1.0, 1.0);
    auto line = std::make_shared<Line>(*p1, *p2);
    auto circle = std::make_shared<Circle>(*p2, 5.0);

    // Creating a shape composite object and adding individual shapes to it
    ShapeComposite composite;
    composite.AddShape(p1);
    composite.AddShape(p2);
    composite.AddShape(line);
    composite.AddShape(circle);

    // The composite structure; without nesting
    std::cout << "composite object before nesting: " << std::endl;
    Print(composite, std::cout);

    // Creating another composite and adding shapes to it
    auto nestedCompositePtr = std::make_shared<ShapeComposite>();
    nestedCompositePtr->AddShape(std::make_shared<Point>(2.0, 2.0));
    nestedCompositePtr->AddShape(std::make_shared<Line>(*p2, Point(2.0, 2.0)));
    nestedCompositePtr->AddShape(std::make_shared<Circle>(Point(2.0, 2.0), 3.0));

    // Adding nesting to the first composite
    composite.AddShape(nestedCompositePtr);

    // The composite structure, with nesting
    std::cout << "\n\n\ncomposite object after adding nesting: " << std::endl;
    Print(composite, std::cout);
}

// Testing function for PolyLine
void testPolyLine() {
    std::cout << "\n\nTesting PolyLine: " << std::endl;
    auto polyline = std::make_shared<PolyLine>();

    // Adding points to the PolyLine
    polyline->AddPoint(std::make_shared<Point>(0.0, 0.0));
    polyline->AddPoint(std::make_shared<Point>(1.0, 1.0));
    polyline->AddPoint(std::make_shared<Point>(2.0, 2.0));

    std::cout << "Contents of PolyLine: " << *polyline << std::endl;

    std::unique_ptr<ShapeFactory> factory = std::make_unique<ConsoleShapeFactory>();

    // Factory creating a polyline
    std::shared_ptr<Shape> shapePolyLine = factory->CreatePolyLine();

    auto polyline2 = std::dynamic_pointer_cast<PolyLine>(shapePolyLine);

    std::cout << "factory polyline: " << *polyline2 << std::endl;
}

int main() {
    test();
    test2();
    testPolyLine();
    return 0;
}