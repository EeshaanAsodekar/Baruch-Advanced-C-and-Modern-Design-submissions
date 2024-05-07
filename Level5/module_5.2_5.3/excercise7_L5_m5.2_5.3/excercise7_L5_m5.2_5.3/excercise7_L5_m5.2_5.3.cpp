#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string text("Quick brown fox");
    std::regex vowels("a|e|i|o|u");

    std::string replaced_text = std::regex_replace(text, vowels, "*");

    std::cout << replaced_text << std::endl;

    return 0;
}
