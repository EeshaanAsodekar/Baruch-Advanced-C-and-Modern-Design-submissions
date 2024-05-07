#include <iostream>
#include <memory>

// given class structure
// Subquestion (a)
class C1
{
private:
    //double* d; OLD WAY
    std::shared_ptr<double> d;
public:
    C1(std::shared_ptr<double> value) : d(value) {}
    virtual ~C1() { std::cout << "\nC1 destructor\n"; }
    void print() const { std::cout << "Value " << *d << "\n"; }
};

class C2
{
private:
    //double* d; OLD WAY
    std::shared_ptr<double> d;
public:
    C2(std::shared_ptr<double> value) : d(value) {}
    virtual ~C2() { std::cout << "\nC2 destructor\n"; }
    void print() const { std::cout << "Value " << *d << "\n"; }
};

// Subquestion (c)
class Point {
public:
    Point(double x, double y) : x_(x), y_(y) {}
    void X(double x) { x_ = x; }
    void Y(double y) { y_ = y; }
    double X() const { return x_; }
    double Y() const { return y_; }
private:
    double x_, y_;
};


class C1_point
{
private:
    //double* d; OLD WAY
    std::shared_ptr<Point> d;
public:
    C1_point(std::shared_ptr<Point> value) : d(value) {}
    virtual ~C1_point() { std::cout << "\nC1_point destructor\n"; }
    void print() const { std::cout << "Value " << d->X() << " " << d->Y() << "\n"; }
};

class C2_point
{
private:
    //double* d; OLD WAY
    std::shared_ptr<Point> d;
public:
    C2_point(std::shared_ptr<Point> value) : d(value) {}
    virtual ~C2_point() { std::cout << "\nC2_point destructor\n"; }
    void print() const { std::cout << "Value " << (*d).X() << " " << d->Y() << "\n"; }
};

int main()
{
    std::cout << "Subquestion (b):\n\n";
    // Subquestion (b)
    std::shared_ptr<double> commonValue(new double(3.1415));
    std::cout << "Initial use_count: " << commonValue.use_count() << std::endl; //1
    {
        C1 object1(commonValue);
        std::cout << "use_count after creating object1: " << commonValue.use_count() << std::endl;//2
        object1.print();
    }// object1 destroyed here
    std::cout << "use_count after destroying object1: " << commonValue.use_count() << std::endl;//1
    {
        C2 object2(commonValue);
        object2.print();
        std::cout << "use_count after creating object2: " << commonValue.use_count() << std::endl;//2
    } // object2 is destroyed here

    std::cout << "Final use_count: " << commonValue.use_count() << "\n\n\n" << std::endl; // 1
    
    // the number will be 0 when the program exits.
    
    std::cout << "Subquestion (c):\n\n";
    // Subquestion (c) 
    {
        std::shared_ptr<Point> p(new Point(1.0, 2.0));
        std::cout << "Initial use_count: " << p.use_count() << std::endl;

        {
            C1_point object1(p);
            object1.print();
            std::cout << "use_count after creating object1: " << p.use_count() << std::endl;
        } // object1 is destroyed here

        std::cout << "use_count after destroying object1: " << p.use_count() << std::endl;

        {
            C2_point object2(p);
            object2.print();
            std::cout << "use_count after creating object2: " << p.use_count() << std::endl;
        } // object2 is destroyed here

        std::cout << "Final use_count: " << p.use_count() << std::endl;
    } // p is destroyed here



    std::cout << "\n\nSubquestion (d):\n\n";
    // Suquestion (d)
    std::shared_ptr<double> sp1_(new double(1.0));
    std::shared_ptr<double> sp2_(sp1_);
    std::shared_ptr<double> sp3_;
    sp3_ = sp1_;// assignement
    std::cout << "sp1_==sp2_: " << (sp1_ == sp2_) << "\n";// comparing shared pointers

    
    std::shared_ptr<double> sp1(new double(1.0));
    //std::shared_ptr<int> sp2 = sp1; // sp2 just shares ownership with sp1
    // Transfer ownership from sp1 to sp2 using std::move
    std::shared_ptr<double> sp2 = std::move(sp1);// sp2 now the owner; sp1 set to null
    std::shared_ptr<double> sp3 = sp2;
 
    // Determine if a shared pointer is the only owner of a resource
    if (sp2.unique()) {
        std::cout << "sp2 is the only owner of the resource\n";
    }
    else {
        std::cout << "sp2 is not the only owner of the resource\n";
    }

    // Swap sp2 and sp3
    sp2.swap(sp3);

    // Give up ownership and reinitialise the shared pointer as being empty
    sp3.reset();

    if (sp3 == nullptr) std::cout << "sp3 reinitialized and is now empty";

    return 0;
}
