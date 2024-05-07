#include <unordered_set>
#include <string>
#include <iostream>

struct S
{
    std::string f;
    std::string s;
    S(const std::string& s1, const std::string& s2) : f(s1), s(s2) {}
};

class SHash // Hash for class S
{
public:
    std::size_t operator() (const S& s) const
    {
        std::hash<std::string> hash_fn;
        return hash_fn(s.f + s.s);
    }
};

class SEqual // Equality for S
{
public:
    bool operator ()(const S& lhs, const S& rhs) const
    {
        return (rhs.f == lhs.f && rhs.s == lhs.s);
    }
};

int main()
{
    std::unordered_set<S, SHash, SEqual> mySet;

    // Subquestion (a) Add elements to this unordered set.
    mySet.insert(S("Hello", "World"));
    mySet.insert(S("Foo", "Bar"));
    mySet.insert(S("Footgdf", "Bardsdcdserjy"));
    mySet.insert(S("ghgFoo", "Bar"));
    mySet.insert(S("Ffgtdvstoo", "Barsdfs"));
    mySet.insert(S("Foogdfgki", "Buktntyar"));

    // Subquestion (b) Examine the bucket information for this unordered set.
    std::cout << "Number of buckets: " << mySet.bucket_count() << std::endl;
    for (size_t i = 0; i < mySet.bucket_count(); ++i) {
        std::cout << "Bucket " << i << " contains " << mySet.bucket_size(i) << " elements.\n";
    }

    std::cout << "Load factor: " << mySet.load_factor() << std::endl;
    std::cout << "Max load factor: " << mySet.max_load_factor() << std::endl;
    std::cout << "Max bucket count: " << mySet.max_bucket_count() << std::endl;

    return 0;
}
