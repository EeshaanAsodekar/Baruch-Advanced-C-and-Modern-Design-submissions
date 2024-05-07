// mediator module which will coordinate actions between input, processing, and output modules
export module mediator;

// necessary modules to handle input, processing, and output functionalities
import input;
import process;
import output;

export namespace Mediator {
    // function that orchestrates the reading, processing, and outputting of data
    void run() {
        // Calling the readString function from the Input module to read data from the user
        auto data = Input::readString();

        // Processing the input data by first converting it to uppercase and then reversing the string
        auto processedData = Process::reverseString(Process::toUpperCase(data));

        // Calling the print function from the Output module to display the processed data
        Output::print(processedData);
    }
}
