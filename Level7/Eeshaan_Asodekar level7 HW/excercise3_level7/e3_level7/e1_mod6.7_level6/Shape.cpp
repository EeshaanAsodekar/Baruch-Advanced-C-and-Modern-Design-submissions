#include "Shape.h"

// Default constructor
Shape::Shape() {
    // no data members to initialize
}

// Copy constructor
Shape::Shape(const Shape& shp) {
    // no data members to copy over
}

// Assignment operator
Shape& Shape::operator=(const Shape& shp) {
    // Protect against self-assignment
    if (this != &shp) {// no datamembers to copy 
    }
    return *this; // Return a reference to this object
}

// Pure Virtual destructor
Shape::~Shape() {

}