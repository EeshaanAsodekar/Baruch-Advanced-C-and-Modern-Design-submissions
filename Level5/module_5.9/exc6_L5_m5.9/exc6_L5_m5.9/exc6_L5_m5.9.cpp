#include <iostream>
#include <boost/signals2.hpp>

// signature for the excercise
using SignalType = boost::signals2::signal<void(double&)>;

// Subquestion (a)
// Hardware layer: checks and adjusts the range of the data
void HardwareLayer(double& d) {
    if (d < 2.0 || d > 4.0) {
        std::cout << "Hardware layer adjusting value to 3 because it was out of range.\n";
        d = 3.0;
    }
    else {
        d = 2.5; // some modification
    }
    std::cout << "exiting hardware layer " << std::endl;
}

// Data layer: modifies the data by an algorithm
void DataLayer(double& d) {
    d *= 2; // Example operation
    std::cout << "Data layer doubled the value to: " << d << std::endl;
}

// Communication layer: formats and prints the data
void CommunicationLayer(double& d) {
    std::cout << "Communication layer final value: " << d << std::endl;
}


int main()
{
    // Subquestion (a)
    // signals for each layer
    SignalType signalExterior;
    SignalType signalHardware;
    SignalType signalData;
    SignalType signalCommunication;

    // connect slots to signals
    signalHardware.connect(HardwareLayer);
    signalData.connect(DataLayer);
    signalCommunication.connect(CommunicationLayer);

    // connect the signals from one to another
    signalExterior.connect(signalHardware);
    signalHardware.connect(signalData);
    signalData.connect(signalCommunication);

    // data initialization in the exterior (main)
    double value = -3.7; // example value out of [2.0, 4.0] range

    // start the signal chain from the exterior
    std::cout << "Exterior initialized data to: " << value << std::endl;
    signalExterior(value); // this will trigger subsequent layers because of the chaining

    return 0;
}