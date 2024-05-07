#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

template <typename T> 
struct Storage
{
    // typedef std::list<T, std::allocator<T>> type;
    // using the Alias Templates logic
    using type = std::list<T, std::allocator<T>>;
};

template <typename T>
class Client
{
private:
    typename Storage<T>::type data; // typename remains mandatory
public:
    Client(int n, const T& val) : data(n, val) {}
    void print() const {
        std::for_each(data.begin(), data.end(),
            [](const T& n)->void { std::cout << n << ","; });
        std::cout << '\n';
    }
};

int main()
{
    int n = 10; int val = 2;
    Client<int> myClient(n, val); myClient.print();
    // this gives us the same output as before

    return 0;
}
