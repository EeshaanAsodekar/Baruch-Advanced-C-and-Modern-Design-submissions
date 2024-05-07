#include <iostream>
#include <regex>
#include <string>
#include <vector>

int main() {
    std::regex myReg10("/");
    std::string S3 = "2016/3/15";

    // Subquestion (a) Extract the data 2016, 3 and 15 from this string.
    std::sregex_token_iterator iter(S3.begin(), S3.end(), myReg10, -1);
    std::sregex_token_iterator end;

    // loading extracted data into the vector
    std::vector<std::string> vec(iter, end);
    std::cout << "Extracted data: ";
    for (const auto& str : vec) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    // Subquestion (b) Extract ‘/’ from this string.
    std::sregex_token_iterator iter2(S3.begin(), S3.end(), myReg10, 0);
    // loading the seperators onto the vector
    std::vector<std::string> vec2(iter2, end);
    std::cout << "Extracted separators: ";
    for (const auto& str : vec2) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    /*
    * -1 -> returns the content between the regex matches
    * 0 -> returns the regex matches themselves
    */

    return 0;
}
