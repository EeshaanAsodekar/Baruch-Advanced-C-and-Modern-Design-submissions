#include "ShapeComposite.h"
#include "ShapeVisitor.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "PrintVisitor.h"
#include <memory>
#include <iostream>

// Subquestion (e): Testing Print Visitor
void TestVisitorPattern() {
    // Creating individual shapes
    Point pt1(10, 12);
    Point pt2(2, 8);
    Line ln1(pt1, pt2);
    Circle crcl(pt1, 8);

    // Creating the first composite containing shapes
    ShapeComposite composite1;
    composite1.AddShape(std::make_shared<Point>(pt1));
    composite1.AddShape(std::make_shared<Line>(ln1));
    composite1.AddShape(std::make_shared<Circle>(crcl));

    // Creating a second composite and adding the first composite into it
    ShapeComposite composite2;
    std::shared_ptr<ShapeComposite> compositePtr1 = std::make_shared<ShapeComposite>(composite1);
    composite2.AddShape(std::make_shared<Circle>(crcl));
    composite2.AddShape(compositePtr1);

    // Creating a PrintVisitor to traverse and print the shapes composites
    PrintVisitor printer;

    // testing individual shapes
    std::cout << "\nprinting the individual shapes using the Accept() and PrintVisitor" << std::endl;
    pt1.Accept(printer);
    pt2.Accept(printer);
    ln1.Accept(printer);
    crcl.Accept(printer);

    std::cout << "\nPrinting composite2 contents (includes composite1) using PrintVisitor:\n";
    composite2.Accept(printer);
}

int main() {

    TestVisitorPattern();

    return 0;
}
