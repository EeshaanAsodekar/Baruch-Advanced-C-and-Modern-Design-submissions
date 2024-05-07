#include <iostream>
#include <regex>
#include <string>
#include <set>

int main() {

    // given string and regex
    std::string S2 = "1,1,2,3,5,8,13,21";
    std::regex myReg("(\\d+),?");

    std::set<std::string> resultSet;
    std::set<int> resultSetInt;

    // Create an instance it of sregex_iterator based on S2 and myReg
    for (std::sregex_iterator it = std::sregex_iterator(S2.begin(), S2.end(), myReg); it != std::sregex_iterator(); ++it) {
        // storing the matched string into the sets
        resultSet.insert(it->str());
        resultSetInt.insert(std::stoi(it->str()));
    }

    // printing out the matched string set
    std::cout << "std::set<std::string> result:" << std::endl;
    for (const auto& str : resultSet) {
        std::cout << str << std::endl;
    }

    // printing out the matched int set
    std::cout << "std::set<int> result:" << std::endl;
    for (const auto& num : resultSetInt) {
        std::cout << num << std::endl;
    }

    return 0;
}