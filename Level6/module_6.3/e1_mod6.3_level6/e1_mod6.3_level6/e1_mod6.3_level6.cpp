#include "ShapeComposite.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include <memory>
#include <iostream>

// Subquestion (h): Testing
void test() {
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

int main() {
    test();
    return 0;
}
