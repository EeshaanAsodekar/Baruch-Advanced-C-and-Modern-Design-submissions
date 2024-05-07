#include <iostream>
#include <boost/bimap.hpp>

int main() {
    typedef boost::bimap<std::string, int> my_bimap;
    my_bimap persons;

    // Subquestion (a) Populate the bimap with some names using insert()
    persons.insert(my_bimap::value_type("Apollo", 25));
    persons.insert(my_bimap::value_type("Jenny", 30));
    persons.insert(my_bimap::value_type("Yuan", 35));

    //persons.emplace(my_bimap::value_type("Yuan", 35));

    /*
    * Boost.Bimap does not support emplace() as of the current version. 
    * The emplace() function is a feature of C++11 which allows for more efficient insertion 
    * into containers by constructing the object in place, but it’s not available in Boost.Bimap.
    */

    // Subquestion (b) Print the left and right maps of the my_bimap
    std::cout << "Left map (name -> age):" << std::endl;
    for (auto it = persons.left.begin(); it != persons.left.end(); ++it) {
        std::cout << it->first << " -> " << it->second << std::endl;
    }

    std::cout << "Right map (age -> name):" << std::endl;
    for (auto it = persons.right.begin(); it != persons.right.end(); ++it) {
        std::cout << it->first << " -> " << it->second << std::endl;
    }

    // Subquestion (c) Search for age based on name and search for name based on age
    try {
        std::cout << "Age of Apollo: " << persons.left.at("Apollo") << std::endl;
        std::cout << "Name of person aged 30: " << persons.right.at(30) << std::endl;
    }
    catch (std::out_of_range& e) { // exception handling
        std::cout << "Element not found: " << e.what() << std::endl;
    }

    // Subquestion (d) Iterate in the my_bimap using the third view
    std::cout << "Third view (set of relations):" << std::endl;
    for (auto it = persons.begin(); it != persons.end(); ++it) {
        std::cout << it->left << " <-> " << it->right << std::endl;
    }

    return 0;
}
