#include "ShapeComposite.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include <memory>
#include <iostream>

// Subquestion (e): Testing
void test() {
    // Testing cloning of a Point
    auto originalPoint = std::make_shared<Point>(5.0, 5.0);
    auto clonedPoint = std::shared_ptr<Shape>(originalPoint->Clone());
    std::cout << "Original Point: " << *originalPoint << std::endl;
    std::cout << "Cloned Point: " << *clonedPoint << std::endl;

    // Testing cloning of a Line
    auto originalLine = std::make_shared<Line>(*originalPoint, Point(10.0, 10.0));
    auto clonedLine = std::shared_ptr<Shape>(originalLine->Clone());
    std::cout << "\nOriginal Line: " << *originalLine << std::endl;
    std::cout << "Cloned Line: " << *clonedLine << std::endl;

    // Testing cloning of a Circle
    auto originalCircle = std::make_shared<Circle>(*originalPoint, 15.0);
    auto clonedCircle = std::shared_ptr<Shape>(originalCircle->Clone());
    std::cout << "\nOriginal Circle: " << *originalCircle << std::endl;
    std::cout << "Cloned Circle: " << *clonedCircle << std::endl;

    // Testing cloning of a ShapeComposite
    ShapeComposite originalComposite;
    originalComposite.AddShape(originalPoint);
    originalComposite.AddShape(originalLine);
    originalComposite.AddShape(originalCircle);

    auto clonedComposite = std::shared_ptr<ShapeComposite>(static_cast<ShapeComposite*>(originalComposite.Clone()));
    std::cout << "\nOriginal Composite: " << std::endl;
    Print(originalComposite, std::cout);

    std::cout << "Cloned Composite: " << std::endl;
    Print(*clonedComposite, std::cout);

    // Modifying the original to see if it affects the clone
    originalPoint->x(100.0);  // Changing the original point, which is part of the original composite
    std::cout << "\nModified Original Composite after changing original point's x to 100.0:" << std::endl;
    Print(originalComposite, std::cout);

    std::cout << "\nCloned Composite after original modification (should not change):" << std::endl;
    Print(*clonedComposite, std::cout);
}

void testCopyAndAssignment() {
    std::cout << "\n\nTesting Copy and Assignment on ShapeComposite" << std::endl;
    ShapeComposite originalComposite;
    auto point = std::make_shared<Point>(1.0, 2.0);
    auto line = std::make_shared<Line>(*point, Point(3.0, 4.0));
    auto circle = std::make_shared<Circle>(*point, 5.0);

    originalComposite.AddShape(point);
    originalComposite.AddShape(line);
    originalComposite.AddShape(circle);

    // Using the copy constructor
    ShapeComposite copiedComposite(originalComposite);
    std::cout << "\nOriginal Composite after copy:" << std::endl;
    Print(originalComposite, std::cout);

    std::cout << "Copied Composite:" << std::endl;
    Print(copiedComposite, std::cout);

    // Modifying the original composite
    point->x(10.0); // This will affect both composites if deep copy isn't working
    line->p1(Point(20.0, 20.0)); // This will affect both composites if deep copy isn't working

    std::cout << "\nOriginal Composite after modification:" << std::endl;
    Print(originalComposite, std::cout);

    std::cout << "Copied Composite after modification (should not change):" << std::endl;
    Print(copiedComposite, std::cout);

    // Using the assignment operator
    ShapeComposite assignedComposite;
    assignedComposite = originalComposite;
    std::cout << "\n\nAssigned Composite:" << std::endl;
    Print(assignedComposite, std::cout);

    // Modifying original to test if assignment created a deep copy
    circle->Radius(100.0);
    std::cout << "\nOriginal Composite after second modification:" << std::endl;
    Print(originalComposite, std::cout);

    std::cout << "Assigned Composite after second modification (should not change):" << std::endl;
    Print(assignedComposite, std::cout);
}

int main() {
    test();
    testCopyAndAssignment();
    return 0;
}
