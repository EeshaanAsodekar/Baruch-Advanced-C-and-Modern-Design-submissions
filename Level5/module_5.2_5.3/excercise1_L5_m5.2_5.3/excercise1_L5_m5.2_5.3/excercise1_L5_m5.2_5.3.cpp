#include <regex>
#include <string>
#include <iostream>

// utility fucntion to perform matching
bool match_regex(const std::regex& reg, const std::string& str) {
    return std::regex_match(str, reg);
}

int main() {
    // Subquestion (a)
    std::regex myReg("[a-z]*");
    std::regex myReg2("[a-z]+");

    std::string s1("aza");
    std::string s2("1");
    std::string s3("b");
    std::string s4("ZZ TOP");

    std::cout << "Does 'aza' match the regex '[a-z]*'? " << (match_regex(myReg, s1) ? "Yes" : "No") << std::endl;
    std::cout << "Does '1' match the regex '[a-z]*'? " << (match_regex(myReg, s2) ? "Yes" : "No") << std::endl;
    std::cout << "Does 'b' match the regex '[a-z]*'? " << (match_regex(myReg, s3) ? "Yes" : "No") << std::endl;
    std::cout << "Does 'ZZ TOP' match the regex '[a-z]*'? " << (match_regex(myReg, s4) ? "Yes" : "No") << std::endl;

    std::cout << "Does 'aza' match the regex '[a-z]+'? " << (match_regex(myReg2, s1) ? "Yes" : "No") << std::endl;
    std::cout << "Does '1' match the regex '[a-z]+'? " << (match_regex(myReg2, s2) ? "Yes" : "No") << std::endl;
    std::cout << "Does 'b' match the regex '[a-z]+'? " << (match_regex(myReg2, s3) ? "Yes" : "No") << std::endl;
    std::cout << "Does 'ZZ TOP' match the regex '[a-z]+'? " << (match_regex(myReg2, s4) ? "Yes" : "No") << std::endl;

    // Subquestion (b)
    std::regex myNumericReg("\\d{2}");
    std::string f("34");
    std::string s("345");

    std::cout << "Does '34' match the regex '\\d{2}'? " << (match_regex(myNumericReg, f) ? "Yes" : "No") << std::endl;
    std::cout << "Does '345' match the regex '\\d{2}'? " << (match_regex(myNumericReg, s) ? "Yes" : "No") << std::endl;

    // Subquestion (c)
    std::regex myAltReg("(new)|(delete)");
    std::string s4A("new");
    std::string s5("delete");
    std::string s6("malloc");

    std::cout << "Does 'new' match the regex '(new)|(delete)'? " << (match_regex(myAltReg, s4A) ? "Yes" : "No") << std::endl;
    std::cout << "Does 'delete' match the regex '(new)|(delete)'? " << (match_regex(myAltReg, s5) ? "Yes" : "No") << std::endl;
    std::cout << "Does 'malloc' match the regex '(new)|(delete)'? " << (match_regex(myAltReg, s6) ? "Yes" : "No") << std::endl;

    // Subquestion (d)
    std::regex myReg3("A*");
    std::regex myReg4("A+");
    std::regex myReg5("(\\d{2})");
    //regex myReg6("\\d{2, 4}");
    std::regex myReg7("\\d{1,}");

    std::string testA("1");
    std::cout << "Does '1' match the regex 'A*'? " << (match_regex(myReg3, testA) ? "Yes" : "No") << std::endl;
    std::cout << "Does '1' match the regex 'A+'? " << (match_regex(myReg4, testA) ? "Yes" : "No") << std::endl;
    std::cout << "Does '1' match the regex '(\\d{2})'? " << (match_regex(myReg5, testA) ? "Yes" : "No") << std::endl;
    std::cout << "Does '1' match the regex '\\d{1,}'? " << (match_regex(myReg7, testA) ? "Yes" : "No") << std::endl;

    // Subquestion (e)
    std::cout << std::endl;
    std::regex rC("(\\w)*"); // Alphanumeric (word) A-Za-z0-9
    std::regex rC1("(\\W)*"); // Not a word
    std::regex rC2("[A-Za-z0-9_]*"); // Alphanumeric (word) A-Za-z0-9

    std::string sC1("abc");
    std::string sC2("A12678Z909za");

    std::cout << "Does 'abc' match the regex '(\\w)*'? " << (match_regex(rC, sC1) ? "Yes" : "No") << std::endl;
    std::cout << "Does 'abc' match the regex '(\\W)*'? " << (match_regex(rC1, sC1) ? "Yes" : "No") << std::endl;
    std::cout << "Does 'abc' match the regex '[A-Za-z0-9_]*'? " << (match_regex(rC2, sC1) ? "Yes" : "No") << std::endl;
    std::cout << "Does 'A12678Z909za' match the regex '(\\w)*'? " << (match_regex(rC, sC2) ? "Yes" : "No") << std::endl;
    std::cout << "Does 'A12678Z909za' match the regex '(\\W)*'? " << (match_regex(rC1, sC2) ? "Yes" : "No") << std::endl;
    std::cout << "Does 'A12678Z909za' match the regex '[A-Za-z0-9_]*'? " << (match_regex(rC2, sC2) ? "Yes" : "No") << std::endl;

    return 0;
}