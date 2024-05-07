// this module mimics the output module of a project in a simplified manner
export module output;

import <iostream>;

export namespace Output {
    // function to simply print a processed string onto the console
    void print(const std::string& data) {
        std::cout << "Processed Output: " << data << std::endl;
    }
}
