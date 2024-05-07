#include <boost/functional/hash.hpp>
#include <list>
#include <iostream>

// Point class definition
class Point {
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

// LineSegment class definition
class LineSegment {
public:
    Point p1, p2;

    LineSegment(Point p1, Point p2) : p1(p1), p2(p2) {}
};

// Subquestion (a)
// PointHash
struct PointHash {
    std::size_t operator()(const Point& pt) const {
        std::size_t seed = 0;
        boost::hash_combine(seed, pt.x);
        boost::hash_combine(seed, pt.y);
        return seed;
    }
};

// Subquestion (a)
// LingSegment hashing
namespace boost {
    template<>
    struct hash<LineSegment> {
        std::size_t operator()(const LineSegment& ls) const {
            std::size_t seed = 0;
            PointHash point_hasher;
            boost::hash_combine(seed, point_hasher(ls.p1));
            boost::hash_combine(seed, point_hasher(ls.p2));
            return seed;
        }
    };
}

// Subquestion (c): custom hash function for the point class
struct PointHash_custom{
    std::size_t operator()(const Point& pt) const {
        std::size_t seed = 0;
        // custom computation: add the square of the sum of x and y coordinates
        int sum = pt.x + pt.y;
        boost::hash_combine(seed, sum * sum);
        return seed;
    }
};


int main() {
    // Subquestion (b): list of Point instances
    std::list<Point> points;
    points.push_back(Point(1, 2));
    points.push_back(Point(3, 4));
    points.push_back(Point(5, 6));

    // transform the list of Point instances into a list of hashes; need it for boost::hash_range()
    PointHash point_hasher;
    std::list<std::size_t> hashes;
    for (const auto& point : points) {
        hashes.push_back(point_hasher(point));
    }

    // computing the hash of the list of hashes (of Point instances)
    std::size_t points_hash = boost::hash_range(hashes.begin(), hashes.end());
    std::cout << "Hash of list of points: " << points_hash << std::endl;

    // testing LineSegment hashing
    LineSegment ls(Point(1, 2), Point(3, 4));

    // computing the hash of the LineSegment
    boost::hash<LineSegment> line_segment_hasher;
    std::size_t ls_hash = line_segment_hasher(ls);
    std::cout << "Hash of LineSegment: " << ls_hash << std::endl;


    // testing and comparing custom hashing
    PointHash_custom ph_custom;
    Point pointx(30, 10);
    std::cout << "pointx hash using PointHash: " << point_hasher(pointx) << std::endl;
    std::cout << "pointx hash using PointHash_custom: " << ph_custom(pointx) << std::endl;

    return 0;
}

