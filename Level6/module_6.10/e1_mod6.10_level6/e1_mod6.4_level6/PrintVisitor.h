#pragma once
#ifndef PRINTVISITOR_HPP
#define PRINTVISITOR_HPP

#include <iostream>
#include "ShapeVisitor.h"
#include "ShapeComposite.h"
#include "Point.h"
#include "Circle.h"
#include "Line.h"

// Subquestion (e)
// Print visitor that dumps the values in Shapes to screen (hint: use the << operator code)
class PrintVisitor : public ShapeVisitor {
public:
    void Visit(Point& p) override {
        std::cout << p << std::endl;
    }

    void Visit(Line& l) override {
        std::cout << l << std::endl;
    }

    void Visit(Circle& c) override {
        std::cout << c << std::endl;
    }

    void Visit(ShapeComposite& sc) {
        std::cout << sc << std::endl;
    }
};

#endif // PRINTVISITOR_HPP


