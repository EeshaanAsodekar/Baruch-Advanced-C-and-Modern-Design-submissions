#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <iostream>
#include <string>
#include <tuple>

// Subquestion (c)
// Define the book details as a tuple containing abstract and price
// We need to include both the book abstract and its price as association attributes
typedef std::tuple<std::string, double> BookDetails;

// Subquestion (a) & (c)
// AuthorBookBimap models a 1:N association between authors and book titles
// The association attribute (book details) includes both abstract and price
typedef boost::bimap<boost::bimaps::multiset_of<std::string>, boost::bimaps::set_of<std::string>, boost::bimaps::with_info<BookDetails>> AuthorBookBimap;
typedef AuthorBookBimap::value_type ABPair;

// Subquestion (b)
// Function to print the price of a specific book from a given author
void printBookPrice(const AuthorBookBimap& bimap, const std::string& author, const std::string& title) {
    auto authorRange = bimap.left.equal_range(author); // find all entries for this author
    bool bookFound = false;
    for (auto it = authorRange.first; it != authorRange.second; ++it) {
        if (it->second == title) {
            std::cout << "Price of \"" << title << "\" by " << author << " is $" << std::get<1>(it->info) << std::endl;
            bookFound = true;
            break;
        }
    }
    if (!bookFound) {
        std::cout << "Book not found for the specified author." << std::endl;
    }
}

int main() {
    AuthorBookBimap books;

    books.insert(ABPair("Alice Munro", "Dear Life", BookDetails("A collection of short stories", 20.00)));
    books.insert(ABPair("Alice Munro", "Runaway", BookDetails("Another collection of short stories", 22.50)));
    books.insert(ABPair("Haruki Murakami", "Kafka on the Shore", BookDetails("A novel blending the mundane with the mythic", 18.95)));
    books.insert(ABPair("Haruki Murakami", "1Q84", BookDetails("A novel set in a fictionalized year of 1984", 16.95)));
    books.insert(ABPair("George Orwell", "1984", BookDetails("A dystopian novel by English novelist George Orwell", 12.99)));
    books.insert(ABPair("George Orwell", "Animal Farm", BookDetails("A farm is taken over by its overworked, mistreated animals", 9.99)));

    // Subqestion (b)
    printBookPrice(books, "Alice Munro", "Dear Life");
    printBookPrice(books, "Haruki Murakami", "Kafka on the Shore");
    printBookPrice(books, "George Orwell", "1984");
    printBookPrice(books, "George Orwell", "Animal Farm");
    printBookPrice(books, "Alice Munro", "The Progress of Love");

    return 0;
}
