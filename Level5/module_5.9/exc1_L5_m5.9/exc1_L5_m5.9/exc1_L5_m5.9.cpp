#include <iostream>
#include <boost/signals2.hpp>
#include <iostream>

// Subquestion (a)
// free fucntion
void freeFunctionSlot() {
    std::cout << "Free function slot called\n";
}

// function object 
struct functionObjectSlot {
    void operator()() {
        std::cout << "Function object slot called\n";
    }
};


// Subquestion (b) 
struct MyStruct
{
    double val;
    MyStruct(double v) { val = v; }
    void modify(double newValue)
    {
       val = newValue;
       std::cout << "A third slot " << val << std::endl;
    }
};

int main()
{
    // Subquestion (a)
    // using lambda function
    auto lambdaSlot = []() {
        std::cout << "Lambda slot called\n";
        };

    
    boost::signals2::signal<void()> signal;

    // connect slots to the signal
    signal.connect(lambdaSlot);
    signal.connect(freeFunctionSlot);
    signal.connect(functionObjectSlot());

    // emit the signal
    std::cout << "Subquestion (a) Emitting signal:\n";
    signal();

    // Subuqestion (b)
    boost::signals2::signal<void(double)> signal2;
    MyStruct myStructInstance(10.0);

    signal2.connect(boost::bind(&MyStruct::modify, &myStructInstance, boost::placeholders::_1));

    std::cout << "\nSubquestion (b) Emitting signal2 with member function slot:\n";
    signal2(100.0);  // Emitting the signal with a new value

    // Subquestion (c)
    std::cout << "\nSubquestion (c) Emitting signal after disconnecting lambdaslot :\n";
    signal.disconnect(lambdaSlot);
    signal();

    // Subquestion (d)
    // Define potential emitters
    boost::signals2::signal<void()> signalA;
    boost::signals2::signal<void()> signalB;
    boost::signals2::signal<void()> signalC;
    boost::signals2::signal<void()> signalD;

    // Define slots
    auto slotB = []() {std::cout << "Slot B called\n " << std::endl; };
    auto slotC = []() {std::cout << "Slot C called\n " << std::endl; };
    auto slotD1 = []() {std::cout << "Slot D1 called\n " << std::endl; };
    auto slotD2 = []() {std::cout << "Slot D2 called\n " << std::endl; };

    // making connections
    signalB.connect(signalA);
    signalC.connect(signalB);
    signalD.connect(signalC);
    signalB.connect(slotB);
    signalC.connect(slotC);
    signalD.connect(slotD1);
    signalD.connect(slotD2);

    std::cout << "\nSubquestion (d) Emitting signal D (connected to signals A, B, C):\n";
    signalD();

    // signalC.disconnect(signalB);
    // signalD();
    // Disconnecting signals from one another is not as straightforward as disconnecting slots... we run into errors
    // The direct/indirect and implicit/explicit connections structure in the tree makes it hard

    // Error:
    /*Severity	Code	Description	Project	File	Line	Suppression State	Details
        Error	C2280	'boost::signals2::signal<void (void),boost::signals2::optional_last_value<void>,int,std::less<int>,boost::function<Signature>,boost::function<R (const boost::signals2::connection &)>,boost::signals2::mutex>::signal(const boost::signals2::signal<Signature,boost::signals2::optional_last_value<void>,int,std::less<int>,boost::function<Signature>,boost::function<R (const boost::signals2::connection &)>,boost::signals2::mutex> &)': attempting to reference a deleted function
        with
        [
            Signature=void (void),
            R=void
        ]	exc1_L5_m5.9	C:\devsoft\boost_1_82_0\boost\signals2\detail\signal_template.hpp	530		
    */

    return 0;
}
