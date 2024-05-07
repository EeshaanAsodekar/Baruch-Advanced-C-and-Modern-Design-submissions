#include <unordered_set>
#include <set>
#include <chrono>
#include <iostream>

struct Point {
    int x;
    int y;

    bool operator<(const Point& other) const {
        if (x < other.x) return true;
        if (x > other.x) return false;
        return y < other.y;  // If x is equal, compare y
    }
};

// Subquestion (a): user defined hash for class Point
struct PointHash {
    std::size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
    }
};

struct PointEqual {
    bool operator()(const Point& lhs, const Point& rhs) const {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

// Subquestion (b): user defined hash for class Point
struct PointHash_custom {
    std::size_t operator()(const Point& p) const {
        return p.x * 31 + p.y;  // simple hash function
    }
};

int main() {
    std::unordered_multiset<Point, PointHash, PointEqual> umset;
    std::multiset<Point> mset;


    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    auto dur1 = elapsed;
    auto dur2 = elapsed;

    // Subquestion (a) & (c)
    // inserting points
    for (int i = 0; i < 10000; ++i) {
        Point p{ i, i };

        start = std::chrono::high_resolution_clock::now();
        umset.insert(p);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        dur1 += elapsed;
        
        start = std::chrono::high_resolution_clock::now();
        mset.insert(p);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        dur2 += elapsed;
    }

    std::cout << "\ntime taken to insert on umset: " << dur1.count() << std::endl;
    std::cout << "time taken to insert on mset: " << dur2.count() << std::endl;

    // Subquestion (a) & (c)
    Point x{ 34562, 34562 };
    // measuring processing time for unordered_multiset
    start = std::chrono::high_resolution_clock::now();
    umset.insert(x);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken by unordered_multiset to insert Point x: " << elapsed.count() << " seconds.\n";

    Point findMe{ 999, 999 };
    start = std::chrono::high_resolution_clock::now();
    auto found = umset.find(findMe);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken by unordered_multiset to find Point: " << elapsed.count() << " seconds.\n";

    start = std::chrono::high_resolution_clock::now();
    umset.clear();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken by unordered_multiset to clear: " << elapsed.count() << " seconds.\n";

    // Subquestion (a) & (c)
    // measuring processing time for multiset
    start = std::chrono::high_resolution_clock::now();
    mset.insert(x);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken by multiset to insert Point x: " << elapsed.count() << " seconds.\n";

    start = std::chrono::high_resolution_clock::now();
    auto found2 = mset.find(findMe);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken by unordered_multiset to find Point: " << elapsed.count() << " seconds.\n";

    start = std::chrono::high_resolution_clock::now();
    mset.clear();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken by multiset to clear: " << elapsed.count() << " seconds.\n";

    // Subquestion (b)
    std::cout << "\n\nusing custom defined hash fucntions for unordered_multiset and multiset" << std::endl;
    std::unordered_multiset<Point, PointHash_custom, PointEqual> umset2;

    for (int i = 0; i < 10000; ++i) {
        Point p{ i, i };
        umset2.insert(p);
    }

    start = std::chrono::high_resolution_clock::now();
    umset2.insert(x);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken by unordered_multiset to insert Point x: " << elapsed.count() << " seconds.\n";

    start = std::chrono::high_resolution_clock::now();
    umset2.clear();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken by unordered_multiset to clear: " << elapsed.count() << " seconds.\n";

    return 0;
}
