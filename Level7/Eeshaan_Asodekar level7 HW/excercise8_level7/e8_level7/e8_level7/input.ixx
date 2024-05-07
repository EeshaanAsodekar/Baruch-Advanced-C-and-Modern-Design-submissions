export module input;

import <string>;
import <iostream>;

// this fucntion simply reads in the user input
// this is a simplistic version of an input module of a project
export namespace Input {
    std::string readString() {
        std::cout << "Enter a string: ";
        std::string input;
        std::getline(std::cin, input);
        return input;
    }
}