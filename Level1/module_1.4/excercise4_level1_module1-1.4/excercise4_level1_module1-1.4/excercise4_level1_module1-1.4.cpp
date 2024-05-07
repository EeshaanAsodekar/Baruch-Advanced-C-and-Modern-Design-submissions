#include <iostream>
#include <functional>

using VoidFunctionType = std::function<void(double)>;

using namespace std;

// Class hierarchy
class Shape
{
protected:
    VoidFunctionType f;
public:
    Shape(void (*fptr)(double)) : f(fptr) {}
    void rotate(double d) {
        cout << "inside roatate(); f called from the base Shape class object" << endl;
        return f(d);
    }
};
class Circle : public Shape
{
public:
    Circle(void (*fptr)(double)):Shape(fptr){}

    // overriding the base class's rotate() member function
    // the rotate function in the child and parent can have different implementations
    // or operations
    void rotate(double d) {
        cout << "sindei rotate(); f called from the derived Circle class object" << endl;
        return f(d);
    }
};

void tester(Shape* shape_ptr, const double & input_double) {
    shape_ptr->rotate(input_double);
}

int main()
{
    auto input_function = [](double x) -> void { cout << x << " from the input_function"; };
    double input_double = 1;

    Shape shape_obj(input_function);
    Circle circle_obj(input_function);

    tester(&shape_obj,input_double);
    cout << "\n\n";
    tester(&circle_obj, input_double);

    return 0;
}