#pragma once
#include "ShapeComposite.h"
#include "Point.h"

// Subquestion (b)
// unable to implement in a template template manner; guidance would be much appreciated

// implemeting polyline as a simple shapecomposite of points 
// It is a simple approach to model it as a collection of points
class PolyLine : public Shape {
private:
    ShapeComposite composite;

public:
    PolyLine() = default;
    PolyLine(const PolyLine& other) : composite(other.composite) {}
    PolyLine& operator=(const PolyLine& other) {
        return *this;
    }

    void AddPoint(std::shared_ptr<Point> point) {
        composite.AddShape(point);
    }

    std::ostream& print(std::ostream& os) const override {
        return os << composite;
    }
};
