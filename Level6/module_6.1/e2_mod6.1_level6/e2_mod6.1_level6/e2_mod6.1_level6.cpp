#include <iostream>
#include <type_traits>
#include <vector>
#include "Point.h"
#include "Shape.h"
#include "Line.h"
#include "Circle.h"

void test() {
    // Subquestion (f)
    // Testing the newly added distance and length fucntionality of Point and Line

    // Testing Distance()
    Point p1(3.0, 4.0);
    Point p2(0.0, 0.0);

    std::cout << "point p1: " << p1 << std::endl;
    std::cout << "point p2: " << p2 << std::endl;

    std::cout << "Distance of p1 from the origin: " << p1.Distance() << std::endl;
    std::cout << "Distance of p2 from the origin: " << p2.Distance() << std::endl;

    std::cout << "Distance between p1 and p2: " << p1.Distance(p2) << std::endl;

    // Testing Length()
    // Line between p1 and p2
    Line line(p1, p2);
    std::cout << "\n\nLine 'line': " << line << std::endl;

    std::cout << "Length of the line between p1 and p2: " << line.Length() << std::endl;
}

int main() {
    test();
    return 0;
}