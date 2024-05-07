#pragma once
#ifndef SHAPECOMPOSITE_HPP
#define SHAPECOMPOSITE_HPP

#include "Shape.h"
#include <list>
#include <memory>

class ShapeComposite : public Shape {
private:

    std::list<std::shared_ptr<Shape>> shapes;

    //ShapeComposite(const ShapeComposite& other) = delete;
    //ShapeComposite& operator=(const ShapeComposite& other) = delete;

public:
    ShapeComposite() {}

    // Subquestion (c)
    virtual Shape* Clone() const override {
        auto newComposite = new ShapeComposite();
        for (const auto& shape : shapes) {
            newComposite->AddShape(std::shared_ptr<Shape>(shape->Clone()));
        }
        return newComposite;
    }

    // Subquestion (d)
    ShapeComposite(const ShapeComposite& other) {
        for (const auto& shape : other.shapes) {
            shapes.push_back(std::shared_ptr<Shape>(shape->Clone()));
        }
    }

    // Subquestion (d)
    ShapeComposite& operator=(const ShapeComposite& other) {
        if (this != &other) {
            shapes.clear();
            for (const auto& shape : other.shapes) {
                shapes.push_back(std::shared_ptr<Shape>(shape->Clone()));
            }
        }
        return *this;
    }

    virtual ~ShapeComposite() {
    }

    void AddShape(std::shared_ptr<Shape> s) {
        shapes.push_back(s);
    }

    typedef typename std::list<std::shared_ptr<Shape>>::iterator iterator;
    typedef typename std::list<std::shared_ptr<Shape>>::const_iterator const_iterator;

    iterator begin() { return shapes.begin(); }
    const_iterator begin() const { return shapes.begin(); }

    iterator end() { return shapes.end(); }
    const_iterator end() const { return shapes.end(); }

    size_t count() const { return shapes.size(); }

    std::ostream& print(std::ostream& os) const override {
        os << "ShapeComposite containing " << count() << " shapes:\n";
        for (const auto& shape : shapes) {
            os << *shape << std::endl;
        }
        return os;
    }
};

void Print(const ShapeComposite& sc, std::ostream& os);

#endif // SHAPECOMPOSITE_HPP
