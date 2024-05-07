#include <iostream>

// given class hierarchy from code snippet given in excercise 3
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

// from code snippet given in excercise 4
class Point: public Shape
{
public:
    Point() {}
    virtual void draw() override {}

    // Subquestion (d) - delete the copy constructor and the copy assignment operator
    Point(const Point&) = delete; // copy constructor
    Point& operator=(const Point&) = delete; // copy assignment operator

    // Subquestion (e) - add move semantics
    // Move constructor
    Point(Point&& other) noexcept
    {
        // move logic on the basis of the data members of class Point
    }

    // Move assignment operator
    Point& operator=(Point&& other) noexcept
    {
        if (this != &other)
        {
            // move logic on the basis of the data members of class Point
        }
        return *this;
    }
};

// Subquestion (a) (b) (c)
// function which checks the following porperties for a class who's object it takes as input
// does class have (1) virtual destructor (2) default, copy, move constructors (3) copy assignable/move assignable
template <typename T> void TypeInformationVI(const T& t)
{
    std::cout << "has virtual destructor : " << std::boolalpha
        << std::has_virtual_destructor<T>::value << std::endl;

    std::cout << "has default constructor : " << std::boolalpha
        << std::is_default_constructible<T>::value << std::endl;

    std::cout << "has copy constructor : " << std::boolalpha
        << std::is_copy_constructible<T>::value << std::endl;

    std::cout << "has move constructor : " << std::boolalpha
        << std::is_move_constructible<T>::value << std::endl;

    std::cout << "is copy assignable : " << std::boolalpha
        << std::is_copy_assignable<T>::value << std::endl;

    std::cout << "is move assignable : " << std::boolalpha
        << std::is_move_assignable<T>::value << std::endl;

    std::cout << "\n*********************\n";
}

int main()
{
    Point point;

    TypeInformationVI(point);
}

/* Answers to questions
* 
* Subquestion (d)
* output Before deleting the copy constructor and the copy assignement operator:
has virtual destructor : false
has default constructor : true
has copy constructor : true
has move constructor : true
is copy assignable : true
is move assignable : true

*********************
* 
* output After deleting the copy constructor and the copy assignement operator:
has virtual destructor : false
has default constructor : true
has copy constructor : false
has move constructor : false
is copy assignable : false
is move assignable : false

*********************
* 
* we do not get the same result as before.
* not only is the class point not have a copy constructor and a copy assignment; 
* it is also non-movable.
* This is because when we explicitly delete the copy constructor and the copy assignment operator, 
* the implicitly-declared move constructor and move assignment operator are no longer implicitly declared
* 
* Subquestion (e)
* output after explicitly defining a move constructor and move assignment operator:
has virtual destructor : false
has default constructor : true
has copy constructor : false
has move constructor : true
is copy assignable : false
is move assignable : true

*********************
* 
* we do not get the same result as the orignal code or the modified code in accordance to (d)
* here we can see that since we have explicitly defined the move constructor and the move assignement operator
* the class is move assignable and move constructible
* 
* This was not the case in (d) because This is because having an implicitly defined move-constructor with an 
* explicitly deleted copy-constructor might be dangerous in some cases. Thus if the copy constructor and 
* copy assignment operator are deleted; we must explicitly define the move semantics in order to be able
* to use them.
*/