#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    // Subqestion (a)
    std::vector<int> vec2{ 3,4,5,6,7,5,6,7,8,9,1,2,3,4 };
    std::vector<int> vec3{ 3,4,5,6,7,5,6,7,8,9,1,2,3,4 };

    // Subquestion (b) creating a heap from the vector
    //  converts a regular vector into a max-heap
    std::make_heap(vec2.begin(), vec2.end());
    std::cout << "Heap after make_heap: ";
    auto printVec = [](std::vector<int> vec) {
        for (int num : vec) {
            std::cout << num << " ";
        }
        std::cout << "\n";
        };
    printVec(vec2);
    std::cout << "\n";

    // Subquestion (c) popping the root of the heap
    // swaps the root of the heap with the last element in the range and 
    // then makes the subrange heap again, excluding the last element which was the root.
    // If the underlying non-heap -> (a) undefined behaviour ... final order of container cannot be predicted
    // We must call pop_back() to actually remove the last element, 
    // which pop_heap() has moved from the root.
    std::pop_heap(vec2.begin(), vec2.end());

    std::cout << "Heap after pop_heap (before pop_back): ";
    printVec(vec2);
    std::cout << "\n";
    vec2.pop_back();
    std::cout << "Heap after pop_back: ";
    printVec(vec2);


    std::cout << "\ntrying to pop_heap from an un-heap data structure:\n";
    printVec(vec3);
    std::pop_heap(vec3.begin(), vec3.end());
    printVec(vec3);

    // Subquestion (d) pushing new value onto the heap
    // Before using std::push_heap(), we must add the new element at the end of the container(push_back()), 
    // then push_heap() will reorder it to maintain the heap property.
    // If the underlying container is not a heap, this will lead to undefined behavior, 
    // where the final arrangement of elements does not form a valid heap, potentially disrupting 
    // the intended order and structure of the data.
    // This can cause logical errors in any subsequent heap operations
    vec2.push_back(10);  // must add the element at the end before re-heapifying
    std::push_heap(vec2.begin(), vec2.end());
    std::cout << "\nHeap after push_heap: \n";
    printVec(vec2);
    std::cout << "\n";

    // Subquestion (e) sorting the heap into a sorted collection
    std::sort_heap(vec2.begin(), vec2.end());
    std::cout << "Sorted collection: (vec2) ";
    printVec(vec2);
    std::cout << "\n";

    // Subquestion (f) finding the largest element in the heap
    // We know that the largest element in a (sorted) max-heap is always the root, i.e., 
    // the first element in the vector.
    std::cout << "Largest element in the heap: " << vec2.front() << "\n";

    return 0;
}