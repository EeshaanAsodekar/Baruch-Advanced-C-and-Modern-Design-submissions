#include <iostream>
#include <memory>

class Point {
public:
    Point(double x_, double y_) : x(x_), y(y_) {}
    void X(double x_) { x  = x_; }
    void Y(double y_) { y = y_; }
    double X() const { return x; }
    double Y() const { return y; }
    void print() { std::cout << x << " " << y << std::endl; }
private:
    double x, y;
};

// Subquestion (d)
using DoublePtr = std::unique_ptr<double>;
using IntPtr = std::unique_ptr<int>;
using PointPtr = std::unique_ptr<Point>;

int main() {
    // Subquestion (a)
    try {
        double* d = new double(1.0);
        Point* pt = new Point(1.0, 2.0);

        *d = 2.0;
        pt->X(3.0);
        pt->Y(3.0);

        throw std::runtime_error("An error occurred// and thus a memory leak");

        delete d;
        delete pt;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    // Memory leak occurs here because d and pt are not deleted if an exception is thrown

    // Subquestion (b)
    try {
        // Subquestion (d)
        DoublePtr d(new double(1.0));
        PointPtr pt(new Point(1.0, 2.0));

        *d = 2.0;
        pt->X(3.0);
        pt->Y(3.0);

        throw std::runtime_error("An error occurred// no memory leak");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    // No memory leak occurs here because d and pt are automatically deleted when they go out of scope

    /* Answer to subquestion (b)
    * std::unique_ptr is a smart pointer that retains sole ownership of an object through 
    * a pointer and destroys that object when the unique_ptr goes out of scope. 
    * Even if an exception is thrown, the unique_ptr objects are still automatically deleted 
    * when they go out of scope. This prevents memory leaks, even in the presence of exceptions. 
    * So, with this modification, the memory leak that was present in the original code during the exception 
    * does not happen now.
    */

    // Subquestion (d)

    //  initializing two unique pointers to the same pointer
    int* rawPtr = new int(5);
    IntPtr uPtr1(rawPtr); // This is fine
    //std::unique_ptr<int> uPtr2(rawPtr); // This causes a run time error

    std::cout << *uPtr1 << std::endl;
    //std::cout << *uPtr2 << std::endl;

    // assigning a unique pointer to another unique pointer
    IntPtr uPtra(new int(5)); // This is fine
    //IntPtr uPtrb = uPtra; // causes compile time error

    // transfering ownership
    IntPtr uPtrx(new int(5)); // uPtr1 owns the memory
    IntPtr uPtry = std::move(uPtrx); // uPtr2 now owns the memory, uPtr1 is set to nullptr

    return 0;
}
