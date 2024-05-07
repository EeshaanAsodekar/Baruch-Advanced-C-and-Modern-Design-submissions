#include <iostream>
#include <boost/functional/hash.hpp>

// Subquestion (a)
template <typename T>
void hash_value(std::size_t& seed, const T& val)
{
    boost::hash<T> hasher;
    boost::hash_combine(seed, hasher(val));
}

// Subquestion (a)
template <typename T, typename... Types>
void hash_value(std::size_t& seed, const T& val, const Types&... args)
{
    boost::hash_combine(seed, val);
    hash_value(seed, args...);
}

// Subquestion (b)
template <typename... Types>
std::size_t hash_value(const Types&... args)
{
    std::size_t seed = 0;
    hash_value(seed, args...);
    return seed;
}

// Point class definition
class Point {
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

// hash specialization for Point
namespace boost {
    template <>
    struct hash<Point> {
        std::size_t operator()(const Point& pt) const {
            std::size_t seed = 0;
            boost::hash_combine(seed, pt.x);
            boost::hash_combine(seed, pt.y);
            return seed;
        }
    };
}

int main()
{
    // Subquestion (a) testing variadic hashers
    std::size_t seed1 = 0;
    std::size_t seed2 = 0;
    hash_value(seed1, "Hello", "World");
    hash_value(seed2, "Hello", "World", "Eeshaan");
    std::cout << "seed1: " << seed1 << "\n";
    std::cout << "seed2: " << seed2 << "\n";

    // Subquestion (b) testing heterogenous variadic hashers
    std::size_t seed3 = 0;
    hash_value(seed3, "Hello", 232, true);
    std::cout << "seed3: " << seed2 << "\n";

    Point x(2, 3);
    std::size_t seed4 = 0;
    hash_value(seed4, x);
    std::cout << "seed4: " << seed4 << "\n";

    return 0;
}