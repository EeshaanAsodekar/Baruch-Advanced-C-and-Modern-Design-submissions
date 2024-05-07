#include <iostream>
#include <vector>
#include <queue>

int main()
{
    // Subquestion (a) 
    const auto data = { 10, 5, 20, 30, 25, 7, 40 };
    // default priority queue
    std::priority_queue<int> pq;

    for (int n : data) {
        pq.push(n);
    }

    std::cout << "Default priority queue: ";
    auto print_pq = [](std::priority_queue<int> pq) {
        while (!pq.empty()) {
            std::cout << pq.top() << " ";
            pq.pop();
        }
        std::cout << "\n";
        };

    print_pq(pq);

    // Subquestion (b) 
    // modify the queue using std::greater<int> as the comparator function
    // Given limitation of statically typed nature of C++, 
    // we'll simulate the modification by creating a new min heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> pqMin(std::greater<int>(), std::vector<int>(data.begin(), data.end()));

    std::cout << "Modified priority queue to min heap using std::greater: ";

    while (!pqMin.empty()) {
        std::cout << pqMin.top() << " ";
        pqMin.pop();
    }
    std::cout << "\n";

    // Subquestion (c)
    // Create a priority queue using an underlying data container and a lambda function as the comparator
    auto cmp = [](int left, int right) { return left > right; }; // Comparator lambda function
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pqLambda(cmp, std::vector<int>(data.begin(), data.end()));

    std::cout << "Priority queue with lambda comparator : ";
    
    while (!pqLambda.empty()) {
        std::cout << pqLambda.top() << " ";
        pqLambda.pop();
    }
    std::cout << "\n";

    return 0;
}