#include <iostream>
#include <thread>
#include <atomic>

// given class
struct X
{
    double val;

    X() : val(0.0) {}
    void operator ()() {
        std::cout << "An X " << val << std::endl;
    }
};

// C++11
template <typename T>
using GenericPointerType = std::shared_ptr<T>;
using PointerType = GenericPointerType<X>;

int main()
{
    // Subquestion (a)
    PointerType x(new X);
    x->val = 10;
    std::cout << "x val: " << x->val << std::endl;
    std::cout << "Use count of x: " << x.use_count() << std::endl; // 10

    // Subquestion (b)
    PointerType x2= nullptr;
    std::atomic_store(&x2,x);

    std::cout << "x val: " << x->val << std::endl; // 10
    std::cout << "x2 val: " << x2->val << std::endl; // 10


    std::cout << "Use count of x: " << x.use_count() << std::endl; // 2
    std::cout << "Use count of x2: " << x2.use_count() << std::endl; // 2


    // Subquestion (c)
    PointerType x3 = nullptr;
    std::atomic_exchange(&x3, x);
    std::atomic_exchange(&x3, x2);

    std::cout << "x val: " << x->val << std::endl; // 10
    std::cout << "x2 val: " << x2->val << std::endl; // 10
    std::cout << "x3 val: " << x3->val << std::endl; // 10

    std::cout << "Use count of x: " << x.use_count() << std::endl; // 3
    std::cout << "Use count of x2: " << x2.use_count() << std::endl;// 3
    std::cout << "Use count of x3: " << x3.use_count() << std::endl;// 3

    // Subquestion (e)
    /*
    * In C++11, std::atomic<std::shared_ptr> is not directly supported. 
    * The reason is that std::shared_ptr is not a trivially copyable type, 
    * and std::atomic requires the type to be trivially copyable.
    * 
    * Apart from that, std::atomic_load and std::atomic_store fucntions can be used
    * with std::shared_ptr, but they are not member fucntions of atomic, and they don't
    * make the shared_ptr itself atomic.
    * 
    * atomic<std::shared_ptr> is possible in C++20.
    */

    // Subquestion (f)
    std::cout << "Shared pointers to X lock-free> " << std::boolalpha
        << std::atomic_is_lock_free(&x) << std::endl;

    return 0;
}
