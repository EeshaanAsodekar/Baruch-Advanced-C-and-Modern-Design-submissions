// excercise3_level2_module2-2.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <type_traits>

// given class hierarchy
class Shape
{
public:
    virtual void draw() = 0;
};

class Base
{
private:
    int y;
public:
    Base() {}
    void draw() {}
};

class Point : public Shape
{
public:
    Point() {}
    virtual void draw() override {}
};

// fucntion which checks the following porperties for each object that 
// it takes as input
// is it (1) empty (2) polymorphic (3) abstract
template <typename T> void TypeInformationIV_empty_poly_abs(const T& t)
{ 
    std::cout << "Is class empty? " << std::boolalpha
        << std::is_empty<T>::value << std::endl;
    std::cout << "Polymorphic class type? " << std::boolalpha
        << std::is_polymorphic<T>::value << std::endl;
    std::cout << "Abstract class type? " << std::boolalpha
        << std::is_abstract<T>::value << std::endl;
    std::cout << "\n*********************\n";
}

// fucntion which checks the following porperties  
// for the two classes which it takes as input
// are they (1) same (2) one the base of the other (3) convertible
template <typename T1, typename T2> void TypeInformationIV_same_basederiv_conversion(const T1& t1, const T2& t2)
{
    std::cout << "are classes same? " << std::boolalpha
        << std::is_same<T1,T2>::value << std::endl;

    std::cout << "is first class the base of the second? " << std::boolalpha
        << std::is_base_of<T1, T2>::value << std::endl;

    std::cout << "is first class convertible to the second? " << std::boolalpha
        << std::is_convertible<T1, T2>::value << std::endl;

    std::cout << "\n*********************\n";
}

class Empty_Class {

};

int main()
{
    Base base;
    Point point;
    Empty_Class test;

    // since the Shape class is an abstract class we cannot create objects of the shape class
    // but we can create a point object and pass a reference to it as as Shape
    Shape& shape = point;

    std::cout << "properties of the class test:\n";
    TypeInformationIV_empty_poly_abs(test);
    std::cout << "properties of the class shape:\n";
    TypeInformationIV_empty_poly_abs(shape);
    std::cout << "properties of the class base:\n";
    TypeInformationIV_empty_poly_abs(base);
    std::cout << "properties of the class point:\n";
    TypeInformationIV_empty_poly_abs(point);


    
    std::cout << "properties between shape and base class:\n";
    TypeInformationIV_same_basederiv_conversion(shape, base);
    std::cout << "properties between base and shape class:\n";
    TypeInformationIV_same_basederiv_conversion(base, shape);
    
    std::cout << "properties between shape and point class:\n";
    TypeInformationIV_same_basederiv_conversion(shape, point);
    std::cout << "properties between point and shape class:\n";
    TypeInformationIV_same_basederiv_conversion(point,shape);

    std::cout << "properties between base and point class:\n";
    TypeInformationIV_same_basederiv_conversion(base, point);
    std::cout << "properties between point and base class:\n";
    TypeInformationIV_same_basederiv_conversion(point, base);

    return 0;
}

/*
* Answering the questions:
* 
* Subquestion (a)
* empty classes: Empty_Class
* polymorphic: Shape, Point
* abstract: Shape
* 
* Subquestion (b)
* none of the classes are the same
* 
* Subquestion (c)
* Shape is the base class of the Point class
* 
* Subquestion (d)
* no class an be converted from one to the other
* 
*/