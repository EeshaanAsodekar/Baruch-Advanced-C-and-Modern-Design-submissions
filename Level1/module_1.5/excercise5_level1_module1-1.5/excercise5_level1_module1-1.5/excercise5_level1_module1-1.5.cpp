#include <iostream>
#include <memory>
#include <tuple>
#include <algorithm>

class Shape;
class IODevice;

using ShapePointer = std::shared_ptr<Shape>;
using IODevicePointer = std::shared_ptr<IODevice>;

class IODevice {
public:
    // we both Circle and Line come under class Shape
    virtual void operator<<(const Shape& s) = 0;
};

class Shape {
public:
    virtual void display(IODevice& ioDevice) const = 0;
};

class Circle : public Shape {
public:
    // returning pointers to object, such that
    // it's specfic data members can be rendered when called
    void display(IODevice& ioDevice) const override {
        ioDevice << *this;
    }
};

class Line : public Shape {
public:
    void display(IODevice& ioDevice) const override {
        ioDevice << *this;
    }
};


// I have taken the case of 2 io devices
// we display on the console; and write it to a file
class ConsoleDevice : public IODevice {
public:
    void operator<<(const Shape& s) override {
        std::cout << "Displaying shape on console\n";
    }
};

class FileDevice : public IODevice {
public:
    void operator<<(const Shape& s) override {
        std::cout << "Displaying shape in file\n";
    }
};

class Builder {
public:
    virtual std::tuple<ShapePointer, IODevicePointer> getProduct() {
        return std::make_tuple(getShape(), getIODevice());
    }

    virtual ShapePointer getShape() = 0;
    virtual IODevicePointer getIODevice() = 0;
};

// overriding the getShape() and getIODevice() pure virtual member functions
// of the parent class
class CircleConsoleBuilder : public Builder {
public:
    ShapePointer getShape() override {
        return std::make_shared<Circle>();
    }

    IODevicePointer getIODevice() override {
        return std::make_shared<ConsoleDevice>();
    }
};

class LineFileBuilder : public Builder {
public:
    ShapePointer getShape() override {
        return std::make_shared<Line>();
    }

    IODevicePointer getIODevice() override {
        return std::make_shared<FileDevice>();
    }
};

int main() {
    // displaying the circle on the console
    // and writing the line on a file

    CircleConsoleBuilder circleConsoleBuilder;
    auto product1 = circleConsoleBuilder.getProduct();
    std::get<0>(product1)->display(*std::get<1>(product1));

    LineFileBuilder lineFileBuilder;
    auto product2 = lineFileBuilder.getProduct();
    std::get<0>(product2)->display(*std::get<1>(product2));

    return 0;
}

