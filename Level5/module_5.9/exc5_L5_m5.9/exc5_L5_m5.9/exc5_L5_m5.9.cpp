#include <iostream>
#include <boost/signals2.hpp>
#include <functional>

// Subquestion (a)
// reprogram collections/lists of function pointers to Boost signals2 
class Subject {
private:
    // using Boost Signals2 to manage observers
    boost::signals2::signal<void(double)> signal;

public:
    // to add observer to the signal
    void AddObserver(const boost::function<void(double)>& observer) {
        signal.connect(observer);
    }

    // notify all observers about a change event
    void ChangeEvent(double x) {
        signal(x);
    }
};

// Subquestion (b)
void CPrint(double x)
{
    std::cout << "C function: " << x << std::endl;
}

struct Print{
    void operator() (double x)
    {
        std::cout << "I am a printer " << x << std::endl;
    }
};

struct Database {
    void operator() (double x)
    {
        std::cout << "I am a database " << x << std::endl;
    }
};

struct MathsWhiz {
    int x;
    MathsWhiz(double x_) { x = x_; };
    void operator() (double x)
    {
        std::cout << "I am a MathsWhiz " << x << std::endl;
    }
};

int main()
{
    // Subquestion (c)
    // Create the notifier
    Subject mySubject;

    // Create the attention list
    Print myPrint;
    MathsWhiz myMaths(10.0);
    Database myDatabase;

    mySubject.AddObserver(myPrint);
    mySubject.AddObserver(myMaths);
    mySubject.AddObserver(myDatabase);
    mySubject.AddObserver(&CPrint);

    // Trigger the event
    std::cout << "Give the value: "; 
    double val; 
    std::cin >> val;

    mySubject.ChangeEvent(val);

    // Subquestion (d)
    // the code performs as expected
    // the reprogramming from collections/lists of function pointers to Boost signals2 is successful

    return 0;
}
