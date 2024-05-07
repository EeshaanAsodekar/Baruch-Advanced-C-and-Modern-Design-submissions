#include "ShapeComposite.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "ShapeFactory.h"
#include "ConsoleShapeFactory.h"

#include <memory>
#include <iostream>

#include "ShapeDecorator.h"
#include "NameDecorator.h"

void test() {
    // Creating basic shapes
    std::shared_ptr<Shape> simplePoint = std::make_shared<Point>(1.0, 2.0);
    std::shared_ptr<Shape> simpleLine = std::make_shared<Line>(Point(1.0, 2.0), Point(3.0, 4.0));
    std::shared_ptr<Shape> simpleCircle = std::make_shared<Circle>(Point(5.0, 5.0), 10.0);

    // Decorating shapes with names, passing shared_ptr directly
    NameDecorator namedPoint(simplePoint, "A Point");
    NameDecorator namedLine(simpleLine, "A Line");
    NameDecorator namedCircle(simpleCircle, "A Circle");

    // Printing the decorated shapes
    std::cout << "Original named shapes:" << std::endl;
    std::cout << namedPoint << std::endl;
    std::cout << namedLine << std::endl;
    std::cout << namedCircle << std::endl;

    // modifying the name
    std::cout << "modifying namedPoint name" << std::endl;
    namedPoint.SetName("New name of a Point");
    std::cout << namedPoint << std::endl;
}

int main() {
    test();
    return 0;
}
