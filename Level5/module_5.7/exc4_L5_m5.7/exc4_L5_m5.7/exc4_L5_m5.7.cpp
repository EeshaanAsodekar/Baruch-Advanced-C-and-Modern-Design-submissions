#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <iostream>
#include <string>
#include <functional>

using namespace boost::bimaps;

// Subquestion (a): Various combinations of the data structures mentioned
// Set -> List
using BimapSetList = bimap<set_of<std::string>, list_of<int>>;

// Set -> Set
using BimapSetSet = bimap<set_of<std::string>, set_of<int>>;

// Set -> Unordered Set
using BimapSetUnorderedSet = bimap<set_of<std::string>, unordered_set_of<int>>;

// Multiset -> List
using BimapMultisetList = bimap<multiset_of<std::string>, list_of<int>>;

// Multiset -> Set
using BimapMultisetSet = bimap<multiset_of<std::string>, set_of<int>>;

// Multiset -> Unordered Set
using BimapMultisetUnorderedSet = bimap<multiset_of<std::string>, unordered_set_of<int>>;

// Unordered Set -> List
using BimapUnorderedSetList = bimap<unordered_set_of<std::string>, list_of<int>>;

// Unordered Set -> Set
using BimapUnorderedSetSet = bimap<unordered_set_of<std::string>, set_of<int>>;

// Unordered Set -> Unordered Set
using BimapUnorderedSetUnorderedSet = bimap<unordered_set_of<std::string>, unordered_set_of<int>>;

// Subquestion (c)
// Set -> Set with std::greater comparator for the integer set
using BimapSetSetCustomComparator = bimap<set_of<std::string>, set_of<int, std::greater<>>>;

int main() {
    // Subquestion (a)
    // Set -> List
    BimapSetList bimapSetList;
    bimapSetList.insert(BimapSetList::value_type("Apple", 10));
    std::cout << "Set -> List: " << bimapSetList.left.begin()->first << " -> " << bimapSetList.right.begin()->second << std::endl;

    // Set -> Set
    BimapSetSet bimapSetSet;
    bimapSetSet.insert(BimapSetSet::value_type("Banana", 20));
    std::cout << "Set -> Set: " << bimapSetSet.left.begin()->first << " -> " << bimapSetSet.right.begin()->second << std::endl;

    // Set -> Unordered Set
    BimapSetUnorderedSet bimapSetUnorderedSet;
    bimapSetUnorderedSet.insert(BimapSetUnorderedSet::value_type("Cherry", 30));
    std::cout << "Set -> Unordered Set: " << bimapSetUnorderedSet.left.begin()->first << " -> " << bimapSetUnorderedSet.right.begin()->second << std::endl;

    // Multiset -> List
    BimapMultisetList bimapMultisetList;
    bimapMultisetList.insert(BimapMultisetList::value_type("Date", 40));
    std::cout << "Multiset -> List: " << bimapMultisetList.left.begin()->first << " -> " << bimapMultisetList.right.begin()->second << std::endl;

    // Multiset -> Set
    BimapMultisetSet bimapMultisetSet;
    bimapMultisetSet.insert(BimapMultisetSet::value_type("Elderberry", 50));
    std::cout << "Multiset -> Set: " << bimapMultisetSet.left.begin()->first << " -> " << bimapMultisetSet.right.begin()->second << std::endl;

    // Multiset -> Unordered Set
    BimapMultisetUnorderedSet bimapMultisetUnorderedSet;
    bimapMultisetUnorderedSet.insert(BimapMultisetUnorderedSet::value_type("Fig", 60));
    std::cout << "Multiset -> Unordered Set: " << bimapMultisetUnorderedSet.left.begin()->first << " -> " << bimapMultisetUnorderedSet.right.begin()->second << std::endl;

    // Unordered Set -> List
    BimapUnorderedSetList bimapUnorderedSetList;
    bimapUnorderedSetList.insert(BimapUnorderedSetList::value_type("Grape", 70));
    std::cout << "Unordered Set -> List: " << bimapUnorderedSetList.left.begin()->first << " -> " << bimapUnorderedSetList.right.begin()->second << std::endl;

    // Unordered Set -> Set
    BimapUnorderedSetSet bimapUnorderedSetSet;
    bimapUnorderedSetSet.insert(BimapUnorderedSetSet::value_type("Honeydew", 80));
    std::cout << "Unordered Set -> Set: " << bimapUnorderedSetSet.left.begin()->first << " -> " << bimapUnorderedSetSet.right.begin()->second << std::endl;

    // Unordered Set -> Unordered Set
    BimapUnorderedSetUnorderedSet bimapUnorderedSetUnorderedSet;
    bimapUnorderedSetUnorderedSet.insert(BimapUnorderedSetUnorderedSet::value_type("Kiwi", 90));
    std::cout << "Unordered Set -> Unordered Set: " << bimapUnorderedSetUnorderedSet.left.begin()->first << " -> " << bimapUnorderedSetUnorderedSet.right.begin()->second << std::endl;


    // Subquestion (c)
    // demonstrating a custom comparator
    BimapSetSetCustomComparator bimapCustom;
    bimapCustom.insert(BimapSetSetCustomComparator::value_type("Alpha", 300));
    bimapCustom.insert(BimapSetSetCustomComparator::value_type("XZeta", 1000));
    bimapCustom.insert(BimapSetSetCustomComparator::value_type("Gamma", 500));

    std::cout << "\nWith custom comparator (std::greater<>):\n";
    for (const auto& element : bimapCustom) {
        std::cout << element.left << " -> " << element.right << std::endl;
    }

    return 0;
}
