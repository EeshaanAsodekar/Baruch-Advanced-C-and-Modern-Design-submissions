#include <iostream>
#include <fstream>
#include <string>
#include <boost/system/error_code.hpp>
#include <system_error>

//boost::system::error_condition OpenAndPrintFile(const std::string& filename) {
 std::error_condition OpenAndPrintFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        // if the file couldn't be opened, returning an error condition
        //return make_error_condition(boost::system::errc::no_such_file_or_directory);
        return std::make_error_condition(std::errc::no_such_file_or_directory);
    }

    // if file successfully opened; we print out the contents
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    file.close();
    //return boost::system::error_condition(); // returning a default-constructed error_codition (i.e., no error)
    return std::error_condition(); // returning a default-constructed error_codition (i.e., no error)
}

int main() {
    // opening the existing file
    std::string filename = "text_file.txt";
    //boost::system::error_condition condition = OpenAndPrintFile(filename);
    std::error_condition condition = OpenAndPrintFile(filename);

    if (condition.value() != 0) {
        std::cout << "Failed to open file. Error: " << condition.message() << '\n';
    }
    else {
        std::cout << "File opened and read successfully.\n";
    }

    // trying to open some non existing file
    filename = "some_non_existing_file.txt";
    condition = OpenAndPrintFile(filename);

    if (condition.value() != 0) {
        std::cout << "Failed to open file. Error: " << condition.message() << '\n';
    }
    else {
        std::cout << "File opened and read successfully.\n";
    }

    return 0;
}
