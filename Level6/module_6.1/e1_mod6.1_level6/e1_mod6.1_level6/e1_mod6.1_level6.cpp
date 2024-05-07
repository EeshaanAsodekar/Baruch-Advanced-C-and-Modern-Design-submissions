#include <iostream>
#include <type_traits>
#include <vector>
#include "Point.h"
#include "Shape.h"
#include "Line.h"
#include "Circle.h"

int main() {
    // examining the hierarchy using type_traits
    // Check if Shape is abstract
    std::cout << "Is Shape abstract? " << std::boolalpha << std::is_abstract<Shape>::value << std::endl;

    // Check if Line is derived from Shape
    std::cout << "Is Line derived from Shape? " << std::boolalpha << std::is_base_of<Shape, Line>::value << std::endl;

    // Check if Cirlce is derived from Shape
    std::cout << "Is Shape a base of Circle? " << std::boolalpha << std::is_base_of<Shape, Circle>::value << std::endl;

    // Check if Point is derived from Shape
    std::cout << "Is Shape a base of Point? " << std::boolalpha << std::is_base_of<Shape, Point>::value << std::endl;

    // Check if Circle is a base of Point
    std::cout << "Is Circle a base of Point? " << std::boolalpha << std::is_base_of<Circle, Point>::value << std::endl;
    
    // Test Point class
    std::cout << "Testing Point class:" << std::endl;
    Point defaultPoint;
    Point customPoint(1.5, 2.5);
    Point copiedPoint(customPoint);
    Point assignedPoint;
    assignedPoint = customPoint;
    assignedPoint.x(3.5); 
    assignedPoint.y(4.5);

    std::cout << defaultPoint << std::endl;
    std::cout << customPoint << std::endl;
    std::cout << copiedPoint << std::endl;
    std::cout << assignedPoint << std::endl;

    // Test Line class
    std::cout << "\nTesting Line class:" << std::endl;
    Line defaultLine;
    Line customLine(Point(0, 1), Point(2, 3));
    Line copiedLine(customLine);
    Line assignedLine;
    assignedLine = customLine;
    assignedLine.p1(Point(4, 5)); 
    assignedLine.p2(Point(6, 7));

    std::cout << defaultLine << std::endl;
    std::cout << customLine << std::endl;
    std::cout << copiedLine << std::endl;
    std::cout << assignedLine << std::endl;

    // Test Circle class
    std::cout << "\nTesting Circle class:" << std::endl;
    Circle defaultCircle;
    Circle customCircle(Point(1, 1), 5);
    Circle copiedCircle(customCircle);
    Circle assignedCircle;
    assignedCircle = customCircle;
    assignedCircle.CenterPoint(Point(3, 3)); 
    assignedCircle.Radius(10);

    std::cout << defaultCircle << std::endl;
    std::cout << customCircle << std::endl;
    std::cout << copiedCircle << std::endl;
    std::cout << assignedCircle << std::endl;

    // printing using print fucntions:
    std::cout << "\nprinting using the print() fucntions of each of the shapes" << std::endl;
    defaultPoint.print(std::cout) << std::endl;
    customCircle.print(std::cout) << std::endl;
    customLine.print(std::cout) << std::endl;

    return 0;
}   