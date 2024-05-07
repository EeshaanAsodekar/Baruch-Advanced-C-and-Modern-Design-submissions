#include <iostream>
#include <thread>
#include <atomic>

int main()
{
    
    // Subquestion (a)
    std::atomic<long long> llong_atomic;
    std::atomic<bool> bool_atomic;
    std::atomic<int> int_atomic;

    std::atomic<short> short_atomic;
    std::atomic<float> float_atomic;
    std::atomic<int*> intptr_atomic;
    std::atomic<char> char_atomic;
    std::atomic<wchar_t> wchar_t_atomic;
    std::atomic<size_t> size_t_atomic;

    // Subquestion (b)
    // which atomic type is lock-free may vary on the basis of the compiler and machine
    // we can check if an atomic type is lock free or notusing the .is_lock_free() on that atomic type variable
    std::cout << "std::atomic<long long> is lock-free? " << (llong_atomic.is_lock_free() ? "Yes" : "No") << '\n';
    std::cout << "std::atomic<bool> is lock-free? " << (bool_atomic.is_lock_free() ? "Yes" : "No") << '\n';
    std::cout << "std::atomic<int> is lock-free? " << (int_atomic.is_lock_free() ? "Yes" : "No") << '\n';
    std::cout << "std::atomic<short> is lock-free? " << (short_atomic.is_lock_free() ? "Yes" : "No") << '\n';
    std::cout << "std::atomic<float> is lock-free? " << (float_atomic.is_lock_free() ? "Yes" : "No") << '\n';
    std::cout << "std::atomic<int*> is lock-free? " << (intptr_atomic.is_lock_free() ? "Yes" : "No") << '\n';
    std::cout << "std::atomic<char> is lock-free? " << (char_atomic.is_lock_free() ? "Yes" : "No") << '\n';
    std::cout << "std::atomic<wchar_t> is lock-free? " << (wchar_t_atomic.is_lock_free() ? "Yes" : "No") << '\n';
    std::cout << "std::atomic<size_t> is lock-free? " << (size_t_atomic.is_lock_free() ? "Yes" : "No") << '\n';

    // Subquestion (c)
    std::atomic<int> atomicInt1(5);  // atomic integer with initial value 5
    std::atomic<int> atomicInt2(10);  // atomic integer with initial value 10

    std::cout << "Before: atomicInt1 = " << atomicInt1 << ", atomicInt2 = " << atomicInt2 << '\n';

    // atomically replace the value of atomicInt1 with the value of atomicInt2
    atomicInt1.store(atomicInt2.load());

    std::cout << "After: atomicInt1 = " << atomicInt1 << ", atomicInt2 = " << atomicInt2 << '\n';

    // Subquestion (d)

    std::atomic<int> atomicInt(10);  // atomic integer with initial value 10

    int value = atomicInt.load();  // atomically load the value of atomicInt

    std::cout << "current value of atomicInt: " << value << '\n';  // prints "Value: 10"

    return 0;
}