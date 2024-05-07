#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string myText("The rain in Spain stays mainly on the plain");
    std::regex mySearchReg("(rain)|(Spain)");

    std::smatch matchResults;

    if (std::regex_search(myText, matchResults, mySearchReg)) {
        std::cout << "mySearchReg match Match found: " << matchResults.str() << std::endl;
    }
    else {
        std::cout << "mySearchReg match not found." << std::endl;
    }

    return 0;
}
