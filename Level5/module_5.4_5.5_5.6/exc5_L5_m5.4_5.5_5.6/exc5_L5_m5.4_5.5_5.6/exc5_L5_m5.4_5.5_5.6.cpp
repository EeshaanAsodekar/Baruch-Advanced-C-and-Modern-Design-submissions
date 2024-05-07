#include <unordered_set>
#include <iostream>

// size_t desired_bucket_size argument is needed for rehashing requirement (d)
template <typename Key, typename Hash, typename EqPred>
void BucketInformation(std::unordered_set<Key, Hash, EqPred>& c, size_t desired_bucket_size) {
    // Subquestion (a) Show the number of buckets and the maximum number of possible buckets.
    std::cout << "Number of buckets: " << c.bucket_count() << std::endl;
    std::cout << "Max number of buckets: " << c.max_bucket_count() << std::endl;

    // Subquestion (b) Show current load factor and the current maximum load factor.
    std::cout << "Current load factor: " << c.load_factor() << std::endl;
    std::cout << "Max load factor: " << c.max_load_factor() << std::endl;

    // Subquestion (c) Show the size of each bucket.
    for (size_t i = 0; i < c.bucket_count(); ++i) {
        std::cout << "Bucket " << i << " size: " << c.bucket_size(i) << std::endl;
    }

    // Subquestion (d) Rehash the container so that it has a bucket size of at least some given size.
    c.rehash(desired_bucket_size);
    std::cout << "Number of buckets after rehash: " << c.bucket_count() << std::endl;
}

int main() {
    // Testing BucketInformation
    std::unordered_set<int> my_set = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    size_t desired_bucket_size = 20;
    BucketInformation(my_set, desired_bucket_size);

    return 0;
}