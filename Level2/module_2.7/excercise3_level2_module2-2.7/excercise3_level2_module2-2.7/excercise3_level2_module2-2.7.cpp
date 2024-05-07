#include <iostream>
#include <tuple>
#include <string>
#include <system_error>

std::tuple<int, std::string, std::string> getErrorConditionDetails(const std::error_condition& ec) {
	return std::make_tuple(ec.value(), ec.message(), ec.category().name());
}

int main()
{
	// Subquestion (a)
	std::error_condition ec1ioError = std::make_error_condition(std::errc::io_error);
	std::error_condition ec2networkUnreachable = std::make_error_condition(std::errc::network_unreachable);
	std::error_condition ec3noSuchFileOrDirectory = std::make_error_condition(std::errc::no_such_file_or_directory);
	std::error_condition ec4notASocket = std::make_error_condition(std::errc::not_a_socket);
	std::error_condition ec5permissionDenied = std::make_error_condition(std::errc::permission_denied);

	// Subquestion (b)
	std::error_condition ec_128_gen(128, std::generic_category());

	// Subquestion (c)
	std::error_condition ecioErr= std::make_error_condition(std::io_errc::stream);

	// accessing the message of each of the error condition
	std::cout << "io_error: " << ec1ioError.message() << '\n';
	std::cout << "network_unreachable: " << ec2networkUnreachable.message() << '\n';
	std::cout << "no_such_file_or_directory: " << ec3noSuchFileOrDirectory.message() << '\n';
	std::cout << "not_a_socket: " << ec4notASocket.message() << '\n';
	std::cout << "permission_denied: " << ec5permissionDenied.message() << '\n';
	std::cout << "custom_error: " << ec_128_gen.message() << '\n';
	std::cout << "io_errc: " << ecioErr.message() << '\n';

	// we can access the error condition properties using the getErrorConditionDetails() function
	// we designed in the last excercise
	auto details1 = getErrorConditionDetails(ec1ioError);
	std::cout << "Error Condition 1: " << std::get<1>(details1) << ", Value: " << std::get<0>(details1) << ", Category: " << std::get<2>(details1) << '\n';


	return 0;
}

