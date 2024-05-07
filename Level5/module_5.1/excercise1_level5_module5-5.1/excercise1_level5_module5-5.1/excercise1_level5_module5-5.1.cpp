#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>

int main() {

    // Subquestion (a) Trim leading and trailing blanks
    std::string str1 = "   Hello, World!   ";
    boost::trim(str1);  // modifies the input string
    std::cout << "trimmed str1: " << str1 << std::endl;

    std::string str2 = "   Hello, World!   ";
    std::string str2_trimmed = boost::trim_copy(str2);  // Creates a copy of the input string
    std::cout << "str2_trimmed: " << str2_trimmed << std::endl;

    // Subquestion (b) Trim leading and trailing characters using different predicates
    std::string stra = "AAAHello, World!AAA";
    boost::trim_if(stra, boost::is_any_of("A"));  // Modifies the input string
    std::cout << "trimmed stra: " << stra << std::endl;

    std::string strb = "BBBHello, World!BBB";
    std::string strb_trimmed = boost::trim_copy_if(str2, boost::is_any_of("B"));  // Creates a copy of the input string
    std::cout << "strb_trimmed: " << strb_trimmed << std::endl;

    std::string strc = "CCC Hello, World! CCC";
    boost::trim_left_if(strc, boost::is_any_of("C"));  // Trims leading characters
    std::cout << "strc: " << strc << std::endl;

    std::string strd = "DDD Hello, World! DDD";
    boost::trim_right_if(strd, boost::is_any_of("D"));  // Trims trailing characters
    std::cout << "strd: " << strd << std::endl;

    std::string stre = "EEE Hello, World! EEE";
    boost::trim_if(stre, boost::is_any_of("E") || boost::is_space());  // Trims leading and trailing characters or spaces
    std::cout << "stre: " << stre << std::endl;

    std::string strf = "FFF Hello, World! FFF";
    boost::trim_if(strf, boost::is_any_of("F") && !boost::is_space());  // Trims leading and trailing characters but not spaces
    std::cout << "strf: " << strf << std::endl;

    // c) Test if a string starts or ends with a given string
    std::string str4 = "Hello, World";
    bool starts_with_hello = boost::starts_with(str4, "hello");  // Case-sensitive
    bool ends_with_world = boost::iends_with(str4, "WORLD");  // Case-insensitive
    std::cout << std::boolalpha << "starts with Hello: " << starts_with_hello << ", " << "ends with (case inst.) WORLD: " << ends_with_world << std::endl;

    // d) Test if a string contains another string
    std::string str5 = "Hello, World!";
    bool contains_world = boost::contains(str5, "World");  // Case-sensitive
    bool icontains_world = boost::icontains(str5, "WORLD");  // Case-insensitive
    std::cout << std::boolalpha << "contains World: " << contains_world << ", " << "contains (case inst.) WORLD: " << icontains_world << std::endl;

    // Test if two strings are equal
    std::string str6 = "Hello, World!";
    std::string str7 = "hello, world!";
    bool strings_equali = boost::iequals(str6, str7);  // Case-insensitive
    bool strings_equal = boost::equals(str6, str7);  // Case-insensitive
    std::cout << std::boolalpha << "Are strings equal (case inst.): " << strings_equali << std::endl;
    std::cout << std::boolalpha << "Are strings equal: " << strings_equal << std::endl;

    return 0;
}
