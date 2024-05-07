#pragma once
#ifndef NAMEDECORATOR_HPP
#define NAMEDECORATOR_HPP

#include "ShapeDecorator.h"
#include <iostream>
#include <string>

// Subquestion (f): NameDecorator that derives from ShapeDecorator
class NameDecorator : public ShapeDecorator {
private:
    // Subquestion (g): private var that holds the name (String)
    std::string name;

public:
    // Subquestion (h): Default constructor that calls the base class constructor and sets the name to an empty string
    NameDecorator() : ShapeDecorator(), name("") {}

    // Subquestion (i): Constructor that has a Shape* and a std::string as an argument
    NameDecorator(std::shared_ptr<Shape> shape, const std::string& nm) : ShapeDecorator(shape), name(nm) {}

    // Subquestion (j)
    // Method to return the name
    std::string GetName() const {
        return name;
    }

    // Subquestion (j)
    // Method to set the name
    void SetName(const std::string& nm) {
        name = nm;
    }

    // Subquestion (k)
    Shape* Clone() const override {
        std::shared_ptr<Shape> clonedShape = std::shared_ptr<Shape>(this->GetShape()->Clone());
        NameDecorator* clonedDecorator = new NameDecorator(clonedShape, this->GetName());
        return clonedDecorator;
    }


    // Implementation of the print function that includes the name
    std::ostream& print(std::ostream& os) const override {
        os << "NameDecorator(Name: " << name << ", Shape: ";
        if (GetShape() != nullptr) {
            GetShape()->print(os);
        }
        else {
            os << "null";
        }
        os << ")";
        return os;
    }

    virtual ~NameDecorator() override {}
};

#endif // NAMEDECORATOR_HPP


