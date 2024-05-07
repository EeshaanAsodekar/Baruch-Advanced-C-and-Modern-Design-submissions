#include <iostream>
#include <functional>
#include <array>

// given class hierarchy
class Shape
{
public:
    virtual void rotate(double d) = 0;
};

class Circle : public Shape
{
public:
    void rotate(double d) override { std::cout << "c\n"; }
};

class Line : public Shape
{
public:
    void rotate(double d) override { std::cout << "l\n"; }
};

// given class
class Valve
{
public:
    void rotate(double d) { std::cout << "v\n"; }
};

// Subquestion (a)
// template variadic function
template <typename T, typename... Types>
void rotate(T& arg, Types&... args);

// termination/tail function
template <typename T>
void rotate(T& arg);

using namespace std;
int main()
{
    Circle circle;
    Line line;
    Valve valve;

    double factor = 2.0;

    // We can in essence create compile-time aggregates/whole
    // part objects on the fly. We only need to write one function.
    
    //auto rotate = bind1st<double>(rotate_variadic, 1.0);

    //rotate(factor, circle);
    //rotate(factor, circle, line);
    //rotate(factor, circle, valve);
    //rotate(factor * 2, circle, valve, line);

    // since we cannot define a .rotate() for the type double
    // the argument factor was removed.

    cout << "\nrotate() performed using template variadic function approach" << endl;

    // code achives the desired outcome
    rotate(circle);
    cout << "\n----------------------------------\n";
    rotate(circle, line);
    cout << "\n----------------------------------\n";
    rotate(circle, valve);
    cout << "\n----------------------------------\n";
    rotate(circle, valve, line);
    

    cout << "\n\n\n\nrotate() performed on array of elements of type Shape*" << endl;
    // Subquestion (b)
    array<Shape*, 5> shapeList{ &circle, &line, &circle, &circle, &line };
    
    double factor2 = 20.0;
    for (auto& elem : shapeList)
    {
        elem->rotate(factor2);
        cout << "-------\n";
    }

    /*Answer to Subquestion (b)
    * we cannot include any object of class Valve in this array because the array is meant to hold 
    * addresses of Shape class objects. Valve are not included in the class hierarchy of the abstract class Shape
    * as are the Circle and Line classes. Valve are an seperate, unrelated class.
    * 
    * We can include the objects of class Valve in the variadic approach because the approach
    * allows the inclusion of an object of any class as long as the class
    * has a rotate() member function implemented; which the Valve class does.
    * 
    * We cannot include an object of a class which does not have a rotate() member fucntion implemented
    */

    return 0;
}

// Subquestion (a)
template <typename T, typename... Types>
void rotate(T& arg,Types&... args)
{   
    // a double is required as the argument for the arg.rotate() member fuctions
    // although that value does not control or modify any of the operations of arg.rotate()
    double x=1;
    arg.rotate(x);
    rotate(args...);
}

// Subquestion (a)
template <typename T>
void rotate(T& arg)
{
    double x = 10;
    arg.rotate(x);
}
