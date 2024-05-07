#include <iostream>
#include <functional>

using namespace std;

using VoidFunctionDouble = function<void(double)>;

class Shape
{
private:
    VoidFunctionDouble f;
public:
    Shape(void (*fptr)(double x)) : f(fptr){};

    void execute(const double& input) { return f(input); }

    void switchFunction(void (*fptr)(double x))
    {
        cout << "switched function!" << endl;
        f = fptr;
    }
};

int main()
{
    double input = 2.0;
    auto square_print = [](double x) -> void {cout << (x * x);};
    auto cube_print = [] (double x) -> void {cout << (x * x * x);};
    
    Shape shape_obj(square_print);
    cout << "function wrapper f initilized to square_print" << endl;


    shape_obj.execute(input);

    cout << "\n\n";

    shape_obj.switchFunction(cube_print);
    cout << "function wrapper f switched to cube_print" << endl;

    shape_obj.execute(input);

    return 0;
}