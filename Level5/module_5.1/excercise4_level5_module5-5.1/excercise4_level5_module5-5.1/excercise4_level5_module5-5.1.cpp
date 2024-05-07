#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <list>
#include <vector>
#include <tuple>
#include <iostream>

// given data structure
using Data = std::tuple<boost::gregorian::date, std::vector<double>>;
using ResultSet = std::list<Data>;

ResultSet processCSV(const std::string& filename) {
    ResultSet resultSet;
    std::ifstream file(filename);
    std::string line;

    // skip the column name line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> fields;
        // splitting on the comma
        boost::split(fields, line, boost::is_any_of(","));

        // the first element in a the line is a date
        boost::gregorian::date date = boost::gregorian::from_string(fields[0]);
        std::vector<double> data;

        // processing the numerical data
        for (size_t i = 1; i < fields.size(); ++i) {
            data.push_back(boost::lexical_cast<double>(fields[i]));
        }

        // appending the processes line
        resultSet.push_back(Data(date, data));
    }

    return resultSet;
}

void printResultSet(const ResultSet& resultSet) {
    for (const auto& data : resultSet) {
        std::cout << boost::gregorian::to_simple_string(std::get<0>(data)) << ": ";

        for (double value : std::get<1>(data)) {
            std::cout << value << " ";
        }

        std::cout << std::endl;
    }
}

int main() {
    // testing the processCSV() function
    ResultSet resultSet = processCSV("data.csv");

    printResultSet(resultSet);

    return 0;
}
