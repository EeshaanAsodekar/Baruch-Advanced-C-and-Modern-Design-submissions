#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

// Subquestion (a)
std::set<char> removeCommon(std::set<char> s1, std::set<char> s2) {
    std::set<char> s3;

    // Required output set-> {b,c,d,k}
    std::copy_if(s1.begin(), s1.end(), std::inserter(s3, s3.begin()),
        [&](const char& c) {
            return s2.find(c) == s2.end();
        });

    return s3;
}

// Subquestion (b)
class Point {
public:
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    double distance(const Point& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }

    // to compare two points
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    // required for std::set to order its elements
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

std::set<Point> transformPointVec(std::vector<Point> v, const Point & p, const double & threshold) {
    std::set<Point> s;
    for (auto point : v) {
        // unique
        if (s.find(point) == s.end()) {
            // falls within distance
            double dist = point.distance(p);
            if (dist <= threshold)
                s.insert(point);
        }
    }
    return s;
}

auto printPointSet = [](std::set<Point> s){
    for (const auto& point : s) {
        std::cout << "(" << point.x << ", " << point.y << ") ";
    }
    std::cout << std::endl;
};

// Subquestion (c)
// Trim all leading and trailing blanks (space, tabs etc.) from the string.
std::string trim(const std::string& str) {
    auto start = std::find_if_not(str.begin(), str.end(), ::isspace);
    auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
    return (start < end) ? std::string(start, end) : "";
}

// Trim all leading and trailing blanks based on a unary predicate.
template <typename UnaryPredicate>
std::string trim_if(const std::string& str, UnaryPredicate p) {
    auto start = std::find_if_not(str.begin(), str.end(), p);
    auto end = std::find_if_not(str.rbegin(), str.rend(), p).base();
    return (start < end) ? std::string(start, end) : "";
}

// Produce a vector of strings from a character-separated string.
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Join two strings.
std::string join(const std::string& str1, const std::string& str2) {
    return str1 + str2;
}

int main()
{
    auto printSet = [](std::set<char> s) {
    for (const auto& element : s) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    };

    // Subquestion (a)
    std::set<char> s1{ 'a','b', 'c', 'd', 'e','k' };
    std::set<char> s2{'a','e' };
    auto s3 = removeCommon(s1,s2);
    printSet(s3);

    // Subquestion (b)
    std::vector<Point> pointv1{Point(2,2),Point(2,2), Point(2,2), Point(2,17), Point(2,2), Point(3,3), };
    Point ref(0, 0);
    auto resSet = transformPointVec(pointv1,ref,5);
    std::cout << "\nresSet:" << std::endl;
    printPointSet(resSet);

    // Subqestion (c)
    std::string str = "   Hello, World!   ";
    std::cout << "trimmed:" << trim(str) << std::endl;  // prints: "Hello, World!"

    std::string str2 = "123Hello, World!321";
    std::cout << "trim_if:" << trim_if(str2, std::isdigit) << std::endl;  // prints: "Hello, World!"

    std::string str3 = "Hello,World!";
    std::vector<std::string> tokens = split(str3, ',');
    for (const auto& token : tokens) {
        std::cout << token << std::endl;  // prints: "Hello" and "World!"
    }

    std::string str4 = "Hello, ";
    std::string str5 = "World!";
    std::cout << join(str4, str5) << std::endl;  // prints: "Hello, World!"

    return 0;
}
