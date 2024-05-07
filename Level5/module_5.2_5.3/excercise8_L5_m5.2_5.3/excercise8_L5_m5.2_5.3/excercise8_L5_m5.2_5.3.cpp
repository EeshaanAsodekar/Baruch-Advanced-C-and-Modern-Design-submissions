#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <regex>
#include <boost/date_time/gregorian/gregorian.hpp>

// given data structure
using Data = std::tuple<boost::gregorian::date, std::vector<double>>;
using ResultSet = std::list<Data>;

ResultSet parseCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    // regex pattern to match the row format
    std::regex rowPattern(R"(^- (\d{4}-\d{2}-\d{2}),([\d\.]+),([\d\.]+),([\d\.]+),([\d\.]+),(\d+),([\d\.]+)$)");
    std::smatch match;
    ResultSet resultSet;

    if (file.is_open()) {
        // skip the column name lines
        std::getline(file, line);

        while (std::getline(file, line)) {
            // matching and extracting the line information
            if (std::regex_match(line, match, rowPattern)) {
                // extracting the date
                boost::gregorian::date date(boost::gregorian::from_string(match[1]));
                // extracting the numerical data
                std::vector<double> data = {
                    std::stod(match[2]),
                    std::stod(match[3]),
                    std::stod(match[4]),
                    std::stod(match[5]),
                    static_cast<double>(std::stol(match[6])),
                    std::stod(match[7])
                };
                resultSet.push_back(std::make_tuple(date, data));
            }
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }

    return resultSet;
}

int main() {
    ResultSet resultSet = parseCSV("data.csv");

    // printing the processed data
    for (const auto& data : resultSet) {
        std::cout << boost::gregorian::to_simple_string(std::get<0>(data)) << ": ";
        for (double value : std::get<1>(data)) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
