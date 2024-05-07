#ifndef SHAPECOMPOSITE_HPP
#define SHAPECOMPOSITE_HPP

#include "Shape.h"
#include <list>
#include <memory>

// Subquestion (a):  Create a ShapeComposite class that derives from the Shape class

class ShapeComposite : public Shape {
private:
    // Subquestion (b): private std::list data-member that contains Shape pointers
    std::list<std::shared_ptr<Shape>> shapes; // Using smart pointers

    // Subquestion (c): Private copy constructor and assignment operator
    //ShapeComposite(const ShapeComposite& other) = delete;
    //ShapeComposite& operator=(const ShapeComposite& other) = delete;

public:
    // Default Constructor
    ShapeComposite() {}

    // Virtual destructor
    virtual ~ShapeComposite() {
        // Smart pointers automatically handle memory cleanup
    }

    // Subquestion (d):  AddShape function
    void AddShape(std::shared_ptr<Shape> s) {
        shapes.push_back(s);
    }

    // Subquestion (e): Public typedef for iterators
    typedef typename std::list<std::shared_ptr<Shape>>::iterator iterator;
    typedef typename std::list<std::shared_ptr<Shape>>::const_iterator const_iterator;

    // Subquestion (f): begin() and end() iterator functions
    iterator begin() { return shapes.begin(); }
    const_iterator begin() const { return shapes.begin(); }

    iterator end() { return shapes.end(); }
    const_iterator end() const { return shapes.end(); }

    // Subquestion (g): count of the shape composite list
    size_t count() const { return shapes.size(); }

    // Implementing print function
    std::ostream& print(std::ostream& os) const override {
        //os << "ShapeComposite containing " << count() << " shapes:\n";
        for (const auto& shape : shapes) {
            os << *shape << std::endl;
        }
        return os;
    }
};

// Subquestion (h): print function that recursively prints the composite
void Print(const ShapeComposite& sc, std::ostream& os);

#endif // SHAPECOMPOSITE_HPP