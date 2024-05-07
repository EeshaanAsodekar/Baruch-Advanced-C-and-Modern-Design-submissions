#include <iostream>
#include <type_traits>
#include <vector>
#include "Point.h"
#include "OriginPoint.h"

// Subquestion (d)
void test() {
    Point pt(2.0, 2.0);

    std::cout << "Point: " << pt << std::endl;
    std::cout << "Distance to origin (0,0): " << pt.Distance() << std::endl;

    // change the origin point
    auto neworigin = OriginPoint::instance();
    neworigin->x(2.0);
    neworigin->y(2.0);

    std::cout << "Distance to neworigin (2.0,2.0): " << pt.Distance() << std::endl;
}

int main() {
    test();
    return 0;
}