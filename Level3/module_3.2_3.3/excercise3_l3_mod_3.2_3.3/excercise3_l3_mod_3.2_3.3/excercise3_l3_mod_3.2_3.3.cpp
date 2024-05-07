#include <iostream>
#include <thread>
#include <functional>

struct FunctionObject
{
    int val;
    FunctionObject() : val(0) {}
    FunctionObject(int data) : val(data) {}
    void operator ()()
    {
        std::cout << "\nhello from FunctionObject " << val << std::endl;
    }
};

// ActiveObject class designed according to the given requirements
class ActiveObject {
private:
    std::thread t;
public:
    ActiveObject(std::function<void()> func) : t(func) {}
    ActiveObject() {};
    ~ActiveObject() {
        try {
            if (t.joinable()) {
                t.join(); // ensures the thread finishes before the object is destroyed
            }
        }
        catch(const std::exception& e){
            std::cerr << "A thread could not be joined: " << e.what() << '\n';
        }
    }
};

void thread_func() {
    std::cout << "\nhello from thread function" << std::endl;
}

int main()
{
    // Subquestion (a)
    std::thread t(thread_func);
    t.join();

    // Subquestion (b)
    ActiveObject active_obj1();

    // Subquestion (c)
    FunctionObject fo;
    ActiveObject active_obj2(fo);

    ActiveObject active_obj3([]()->void {
        std::cout << "\nhello from lambda function" << std::endl;
        });
    
    return 0;
}

