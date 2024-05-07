#include <iostream>
#include <system_error>
#include <tuple>
#include <windows.h>

// function to return error code info
std::tuple<int, std::string, std::string> getErrorCodeDetails(const std::error_code& ec) {
    return std::make_tuple(ec.value(), ec.message(), ec.category().name());
}

int main() {
    // Subquestion (a)
    // default error code
    std::error_code ec1;

    // error code with a platform-dependent error code value and an error category
    std::error_code ec2(ERROR_FILE_NOT_FOUND, std::system_category());

    // Subquestion (b)
    // priting out the error code information using getErrorCodeDetails

    auto details1 = getErrorCodeDetails(ec1);
    std::cout << "Error Code 1: " << std::get<0>(details1) << ", Message: " << std::get<1>(details1) << ", Category: " << std::get<2>(details1) << '\n';

    auto details2 = getErrorCodeDetails(ec2);
    std::cout << "Error Code 2: " << std::get<0>(details2) << ", Message: " << std::get<1>(details2) << ", Category: " << std::get<2>(details2) << '\n';

    // Subquestion (c)
    // Testing equality/inequality of instances of std::error_code and std::error_condition
    // both set to errc::no_such_file_or_directory
    std::error_code ec3 = std::make_error_code(std::errc::no_such_file_or_directory);
    std::error_condition econd = std::make_error_condition(std::errc::no_such_file_or_directory);

    if (ec3 == econd) {
        std::cout << "ec3 and econd are equal.\n"; // they are equal!
    }
    else {
        std::cout << "ec3 and econd are not equal.\n";
    }

    return 0;
}
