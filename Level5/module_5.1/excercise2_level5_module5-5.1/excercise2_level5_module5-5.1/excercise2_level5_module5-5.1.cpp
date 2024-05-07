#include <iostream>
#include <boost/algorithm/string.hpp>
#include <tuple>

// Subquestion (b): verify is the password follows the requirements
std::tuple<bool, std::string> checkPassword(std::string input) {
    
    // filtering out the characters
    auto chars = boost::trim_copy_if(input, !(boost::is_upper() || boost::is_lower()));
    
    // password must contain at least 8 characters 
    if (chars.size() < 8) {
        return std::make_tuple(false,"pword must contain min 8 characters");
    }
    
    // must contain digit
    else if (boost::all(input, !boost::is_digit())) {
        return std::make_tuple(false, "pword must contain both digits and characters");
    }
    
    // must have an upper case character
    else if (boost::all(input, !boost::is_upper())) {
        return std::make_tuple(false, "pword needs one upper case character");
    }
    
    // no spaces allowed
    if (boost::contains(input, " ")) {
        return std::make_tuple(false, "pword must not contain any spaces");
    }
    
    // must not have control chracters
    else if (boost::all(input, boost::is_any_of("\*"))) {
        return std::make_tuple(false, "pword can't have control characters");
    }
    
    // all the requirements passed!
    else {
        return std::make_tuple(true, "pword passed!");
    }
}

int main()
{
    // Subquestion (a):
    std::string str1(" abd1 234\*");

    // Recognize digits or letters
    std::cout << std::boolalpha << "digits or letters: " << boost::all(str1, (boost::is_alpha()) || (boost::is_digit()));

    // Recognize digits and not letters
    std::cout << std::boolalpha << "\ndigits and not letters: " << boost::all(str1, (boost::is_digit() && !(boost::is_alpha())));

    // Recognize characters from the range [‘a’,’z’]
    std::cout << std::boolalpha << "\ncharacters from the range a to z: " << boost::all(str1, boost::is_lower()) << std::endl;

    // Subquestion (b): password checker
    std::string pwd1("DanielDuffy1952");
    std::string pwd2("DanielDuffy");
    std::string pwd3("U19520829");
    std::string pwd4("19520829U");

    auto test1 = checkPassword(pwd1);  // true
    auto test2 = checkPassword(pwd2);  // false
    auto test3 = checkPassword(pwd3);  // false
    auto test4 = checkPassword(pwd4);  // false

    // print tuple of fucntion output:
    std::cout << "\n\nchecking passwords: " << std::endl;
    std::cout << std::boolalpha << std::get<0>(test1) << ": " << std::get<1>(test1) << std::endl;
    std::cout << std::boolalpha << std::get<0>(test2) << ": " << std::get<1>(test2) << std::endl;
    std::cout << std::boolalpha << std::get<0>(test3) << ": " << std::get<1>(test3) << std::endl;
    std::cout << std::boolalpha << std::get<0>(test4) << ": " << std::get<1>(test4) << std::endl;

    return 0;
}
