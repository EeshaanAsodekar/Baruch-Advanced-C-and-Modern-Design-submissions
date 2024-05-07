#include <iostream>
#include <system_error>
#include <tuple>

// function to return error condition information in the form of a tuple
std::tuple<int, std::string, std::string> getErrorConditionDetails(const std::error_condition& ec) {
    return std::make_tuple(ec.value(), ec.message(), ec.category().name());
}

int main() {
    // Subquestion (a)
    // creating instances of std::error_condition
    // default constructor
    std::error_condition ec1;

    // value (stored error code; 2) and error category
    std::error_condition ec2(2, std::generic_category());

    // based on std::errc code
    std::error_condition ec3 = std::make_error_condition(std::errc::permission_denied);

    // accessing and printing the error conditon information
    auto details1 = getErrorConditionDetails(ec1);
    std::cout << "Error Condition 1: " << std::get<1>(details1) << ", Value: " << std::get<0>(details1) << ", Category: " << std::get<2>(details1) << '\n';

    auto details2 = getErrorConditionDetails(ec2);
    std::cout << "Error Condition 2: " << std::get<1>(details2) << ", Value: " << std::get<0>(details2) << ", Category: " << std::get<2>(details2) << '\n';

    auto details3 = getErrorConditionDetails(ec3);
    std::cout << "Error Condition 3: " << std::get<1>(details3) << ", Value: " << std::get<0>(details3) << ", Category: " << std::get<2>(details3) << '\n';

    return 0;
}
