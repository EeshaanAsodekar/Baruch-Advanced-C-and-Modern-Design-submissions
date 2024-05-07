#include <iostream>
#include <regex>
#include <string>

int main() {
    std::regex ecmaReg("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");
    
    /*
    * Subquestion (a)
    * The regex subsumes the following kinds of numbers:
    * Integer numbers, which can be positive or negative. For example, 123, -456.
    * Decimal numbers, which can be positive or negative. For example, 123.456, -789.012.
    * Scientific notation, which can be positive or negative for both the base number and the exponent. For example, 1.23e4, -1.23e-4, 123E4, -123E-4.
    */

    // Subquestion (b) and (c)
    std::string testCases[] = { "123", "-456", "123.456", "-789.012", "1.23e4", "-1.23e-4", "123E4", "-123E-4", "abc", "123abc", "123.456.789", "1.23e" };

    for (const auto& testCase : testCases) {
        if (std::regex_match(testCase, ecmaReg)) {
            std::cout << testCase << " is a valid number.\n";
            double num = std::stod(testCase);
            std::cout << "Converted to double: " << num << "\n";
        }
        else {
            std::cout << testCase << " is not a valid number.\n";
        }
    }

    return 0;
}