#include <iostream>
#include <boost/signals2.hpp>


// Free function slot
void freeFunctionSlot() {
    std::cout << "Free function slot called\n";
}

// Function object slot
struct FunctionObjectSlot {
    void operator()() {
        std::cout << "Function object slot called\n";
    }
};

// Class with a member function slot
struct MyStruct {
    double val;
    MyStruct(double v) : val(v) {}
    void modify(double newValue) {
        val = newValue;
        std::cout << "Member function slot called with value " << val << std::endl;
    }
};

// Define slots
void slotA() {
    std::cout << "Slot A\n";
}
void slotB() {
    std::cout << "Slot B\n";
}
void slotC() {
    std::cout << "Slot C\n";
}
void slotD1() {
    std::cout << "Slot D1\n";
}
void slotD2() {
    std::cout << "Slot D2\n";
}

int main()
{
    auto lambdaSlot = []() {
        std::cout << "Lambda slot called\n";
        };

    boost::signals2::signal<void()> signal;


    FunctionObjectSlot functionObject;
    MyStruct myStructInstance(10.0);

    // Subquestion (a)
    signal.connect(1, lambdaSlot);
    signal.connect(2, freeFunctionSlot);
    signal.connect(3, functionObject);
    signal.connect(4, boost::bind(&MyStruct::modify, &myStructInstance, 50.0));
    
    // Subquestion (b)
    std::cout << "Emitting signal:\n";
    signal();
    
    boost::signals2::signal<void()> signal2;

    // Subquestion (a)
    signal2.connect(4, lambdaSlot);
    signal2.connect(3, freeFunctionSlot);
    signal2.connect(2, functionObject);
    signal2.connect(1, boost::bind(&MyStruct::modify, &myStructInstance, 50.0));

    // Subquestion (b)
    std::cout << "\n\nEmitting signal2:\n";
    signal2();

    /*thus, the lower groups get trasnmitted first*/
    // 1 .. 2 .. 3 .. 4 
    // thus, in case of signal2, we have 
    // 1st : myStructInstance
    // 2nd : functionObject
    // 3rd : freeFunctionSlot
    // 4th : lambdaSlot

    boost::signals2::signal<void()> signalA;
    boost::signals2::signal<void()> signalB;
    boost::signals2::signal<void()> signalC;
    boost::signals2::signal<void()> signalD;

    signalA.connect(1, slotA); // Signal A has Slot A
    signalB.connect(1, signalA); // Signal B triggers Signal A
    signalB.connect(2, slotB); //  Signal B does Slot B
    signalC.connect(1, signalB); // Signal C triggers Signal B
    signalC.connect(2, slotC); //  Signal C does Slot C
    signalD.connect(1, signalC); // Signal D triggers Signal C
    signalD.connect(2, slotD1); // Signal D does Slot D1
    signalD.connect(3, slotD2); // Signal D does Slot D2

    std::cout << "\n\nEmitting signal D:\n";
    signalD();

    return 0;
}
