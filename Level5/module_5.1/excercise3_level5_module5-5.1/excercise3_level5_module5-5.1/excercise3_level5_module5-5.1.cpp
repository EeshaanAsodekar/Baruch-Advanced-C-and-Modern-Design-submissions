#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include <vector>
#include <string>

// Subquestion (a) split and join strings
std::string splitAndJoin(const std::string& input) {
    std::vector<std::string> result;
    // split on ",", "/" and "*"
    boost::split(result, input, boost::is_any_of(", / *"));
    // join using "/"
    return boost::join(result, "/");
}

// Subquestion (b) convert string to Boost date
boost::gregorian::date stringToDate(const std::string& dateStr) {
    std::vector<std::string> dateParts;

    // split on "-"
    boost::split(dateParts, dateStr, boost::is_any_of("-"));

    // return boost date
    return boost::gregorian::date(
        boost::lexical_cast<int>(dateParts[0]),
        boost::lexical_cast<int>(dateParts[1]),
        boost::lexical_cast<int>(dateParts[2])
    );
}

// Subquestion (c) convert string to map
std::map<std::string, double> stringToMap(const std::string& str) {
    std::map<std::string, double> result;
    std::vector<std::string> pairs;
    
    // splitting each pair
    boost::split(pairs, str, boost::is_any_of(","));
    
    // loading the map on each pair
    for (const auto& pair : pairs) {
        std::vector<std::string> keyValue;

        // now splitting on the basis of the "=" to get the actual key value pairs
        boost::split(keyValue, pair, boost::is_any_of("="));

        // trimming for any spaces
        boost::trim(keyValue[0]);
        boost::trim(keyValue[1]);

        // loading onto the map
        result[keyValue[0]] = boost::lexical_cast<double>(keyValue[1]);
    }
    return result;
}

int main() {
    // Subquestion (a)
    // testing splitAndJoin function
    std::string sA = "1,2,3,4/5/9*56";
    std::string resultA = splitAndJoin(sA);
    std::cout << "Result of splitAndJoin: " << resultA << std::endl;

    // Subquestion (b)
    // testing stringToDate function
    std::string dateStr = "2015-12-31";
    boost::gregorian::date date = stringToDate(dateStr);
    std::cout << "Result of stringToDate: " << date << std::endl;

    // Subquestion (c)
    // testing stringToMap function
    std::string str = "port = 23, pin = 87, value = 34.4";
    std::map<std::string, double> result = stringToMap(str);
    std::cout << "Result of stringToMap: ";
    // printing the result map
    for (const auto& pair : result) {
        std::cout << pair.first << " = " << pair.second << "; ";
    }
    std::cout << std::endl;

    return 0;
}
