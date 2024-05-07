#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <boost/algorithm/string.hpp>

int main() {
    std::string sA("a = 1, b = 2, c = 3");
    std::regex reg(",\\s*");

    std::sregex_token_iterator iter(sA.begin(), sA.end(), reg, -1);
    std::sregex_token_iterator end;
    
    std::map<std::string, std::string> kv_pairs;

    for (; iter != end; ++iter) {
        // kv is extracted from the content between the "," regex matching
        std::string kv = *iter;
        std::vector<std::string> result;

        // splitting on the "=" and loading the map
        boost::split(result, kv, boost::is_any_of("="));
        if (result.size() == 2) {
            kv_pairs[boost::trim_copy(result[0])] = boost::trim_copy(result[1]);
        }
    }

    for (const auto& kv : kv_pairs) {
        std::cout << kv.first << " : " << kv.second << std::endl;
    }

    return 0;
}
