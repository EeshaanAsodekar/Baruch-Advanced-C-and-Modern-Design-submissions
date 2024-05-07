// this module contains all the processing functions
// we will use them in the mediator module
#include <string>
export module process;

#include <string>
#include <cctype>
#include <algorithm>

export namespace Process {
    // Converts a string to uppercase
    std::string toUpperCase(const std::string& input) {
        std::string result;
        for (char c : input) {
            result += std::toupper(c);
        }
        return result;
    }

    // Reverses the characters in a string
    std::string reverseString(const std::string& input) {
        std::string result = input;
        std::reverse(result.begin(), result.end());
        return result;
    }
}