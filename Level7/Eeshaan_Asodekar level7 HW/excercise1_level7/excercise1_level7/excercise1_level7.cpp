#include <iostream>
#include <tuple>
#include <memory>

#include "Point.h"
#include "Shape.h"
#include "Line.h"
#include "Circle.h"
#include "ShapeFactory.h"
#include "ConsoleShapeFactory.h"

void test() {
    std::unique_ptr<ShapeFactory> factory = std::make_unique<ConsoleShapeFactory>();

    // Testing creating individual shapes
    std::shared_ptr<Shape> shapePoint = factory->CreatePoint();
    std::shared_ptr<Shape> shapeLine = factory->CreateLine();
    std::shared_ptr<Shape> shapeCircle = factory->CreateCircle();

    // Downcasting to appropriate type using dynamic_pointer_cast
    auto point = std::dynamic_pointer_cast<Point>(shapePoint);
    auto line = std::dynamic_pointer_cast<Line>(shapeLine);
    auto circle = std::dynamic_pointer_cast<Circle>(shapeCircle);

    // Displaying the created shapes {individual; the Factory still works}
    if (point != nullptr) {
        std::cout << "Individual Point: " << *point << std::endl;
    }
    if (line != nullptr) {
        std::cout << "Individual Line: " << *line << std::endl;
    }
    if (circle != nullptr) {
        std::cout << "Individual Circle: " << *circle << std::endl;
    }

    // Testing creating all shapes at once using CreateShapes()
    auto shapesTuple = factory->CreateShapes();
    auto tuplePoint = std::get<0>(shapesTuple);
    auto tupleLine = std::get<1>(shapesTuple);
    auto tupleCircle = std::get<2>(shapesTuple);

    // Displaying the tuple shapes created using CreateShapes()
    if (tuplePoint != nullptr) {
        std::cout << "Tuple Point: " << *tuplePoint << std::endl;
    }
    if (tupleLine != nullptr) {
        std::cout << "Tuple Line: " << *tupleLine << std::endl;
    }
    if (tupleCircle != nullptr) {
        std::cout << "Tuple Circle: " << *tupleCircle << std::endl;
    }
}

int main() {
    test();
    return 0;
}

// Subquestion (c)
/*
Original GOF Factory Method:
- Straightforward addition of new products by adding specific factory methods, e.g., CreateRectangle().
- Requires updating the factory interface and all concrete implementations for 
each new shape, which can be cumbersome.
- High cohesion with each method focused on creating a single product, 
adhering to the Single Responsibility Principle.

Modified Tuple-Based Factory Method:
- Adding a new product like Rectangle requires updating the CreateShapes() method's return 
type across all implementations, increasing the effort due to changes in the method signature.
- Changes in product offerings affect the method signature, necessitating widespread updates 
wherever the tuple is utilized.
- The method's cohesion is reduced as it handles the creation of multiple products, 
increasing its responsibilities.

Effort to Add Rectangle:
- Original Design: Introduce a CreateRectangle() method in the ShapeFactory and its concrete factories.
- Modified Design: Alter the CreateShapes() return type to include std::shared_ptr<Rectangle>, 
revise this method in all factories, and update all relevant client code to accommodate 
the new tuple structure.

The original design offers ease of extending the product range with minimal disruption, 
whereas the modified design, despite being efficient in creating and retrieving multiple products 
simultaneously, poses challenges in maintainability and flexibility when modifying the product list.
*/