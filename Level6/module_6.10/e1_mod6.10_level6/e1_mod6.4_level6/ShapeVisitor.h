#pragma once

// Forward Declaring
class Point;
class Circle;
class Line;
class ShapeComposite;

// Subquestion (a)
class ShapeVisitor {
public:
    // abstract Visit() method for each shape in the hierarchy
    virtual void Visit(Point& p) = 0;
    virtual void Visit(Line& l) = 0;
    virtual void Visit(Circle& c) = 0;
    virtual void Visit(ShapeComposite& sc) = 0;
};