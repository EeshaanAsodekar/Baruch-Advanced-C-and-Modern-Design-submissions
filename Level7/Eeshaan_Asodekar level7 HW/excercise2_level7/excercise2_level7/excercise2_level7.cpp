#include <iostream>
#include <tuple>
#include <memory>

#include "Point.h"
#include "Shape.h"
#include "Line.h"
#include "Circle.h"
#include "ShapeFactory.h"
#include "ConsoleShapeFactory.h"
#include "UniversalShapeFactory.h"

// new testing fucntion for excercise 2 of level 7
void testUniversalShapeFactory() {
    UniversalShapeFactory factory;

    // Subquestion (b)
    // Setting up custom factory methods
    factory.createPoint = []() {
        return std::make_shared<Point>(10.0, 20.0);
        };
    factory.createLine = []() {
        auto start = std::make_shared<Point>(10.0, 10.0);
        auto end = std::make_shared<Point>(30.0, 40.0);
        return std::make_shared<Line>(*start, *end);
        };
    factory.createCircle = []() {
        auto center = std::make_shared<Point>(15.0, 15.0);
        return std::make_shared<Circle>(*center, 25.0);
        };

    // Using the factory to create shapes
    auto point = factory.createPoint();
    auto line = factory.createLine();
    auto circle = factory.createCircle();

    // Displaying the shapes created by the UniversalShapeFactory
    if (point != nullptr) {
        std::cout << "Universal Factory Point: " << *point << std::endl;
    }
    if (line != nullptr) {
        std::cout << "Universal Factory Line: " << *line << std::endl;
    }
    if (circle != nullptr) {
        std::cout << "Universal Factory Circle: " << *circle << std::endl;
    }
}

// Subquestion (d)
class NewShapeFactory {
public:
    // The function to take two doubles for coordinates
    std::function<std::shared_ptr<Point>(double, double)> createModifiedPoint;

    NewShapeFactory(ConsoleShapeFactory* factory) {
        // Defining the lambda to match the std::function signature
        createModifiedPoint = [factory](double x_, double y_) {
            auto pointCreator = std::bind(&ConsoleShapeFactory::CreatePoint, factory);
            auto p = std::dynamic_pointer_cast<Point>(pointCreator());
            if (p) {
                p->x(x_);
                p->y(y_);
            }
            return p;
            };
    }
};

void test() {
    ConsoleShapeFactory factory;
    NewShapeFactory nFactory(&factory);

    auto point = nFactory.createModifiedPoint(10.0, 20.0);
    std::cout << "^^ was from the Point constructor; need to figure out how to disable it" << std::endl;
    if (point) {
        std::cout << "Modified Point: (" << point->x() << ", " << point->y() << ")" << std::endl;
    }
    else {
        std::cout << "Failed to create or modify point." << std::endl;
    }
}

int main() {
    testUniversalShapeFactory();
    test();
    return 0;
}

// Subquestion (c)
/*
Strategy Pattern Suitability
- The UniversalShapeFactory using std::function fits well with the Strategy pattern, 
allowing dynamic swapping of object creation logic at runtime.
- Simplifies traditional GOF Strategy pattern by reducing the need for multiple strategy classes. 
Factory methods can be set directly using lambdas or std::bind, enhancing flexibility.

Command Pattern Suitability
- Aligns with the Command pattern, as std::function allows encapsulation of creation commands 
that can be executed later or stored for undo operations.
- Modernizes traditional Command pattern by eliminating multiple command classes and 
using callable objects to streamline command execution and reduce boilerplate.
*/