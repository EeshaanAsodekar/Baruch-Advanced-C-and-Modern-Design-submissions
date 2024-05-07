#include <boost/signals2.hpp>
#include <iostream>

struct BootstrapCheck
{
    // Iterate in slots and return first 'false'
    // value; otherwise, 'true'
    typedef bool result_type;
    template <typename InputIterator>
    bool operator()(InputIterator first, InputIterator last) const
    {
        while (first != last)
        {
            if (!*first)
                return false;
           ++first;
        }
        return true;
    }
};

// Subquestion (b)
bool slot1() {
    std::cout << "Slot 1: true\n";
    return true;
}

bool slot2() {
    std::cout << "Slot 2: false\n";
    return false;
}

bool slot3() {
    std::cout << "Slot 3: true\n";
    return true;
}

int main()
{
    // Subquestion (a)
    boost::signals2::signal<bool(), BootstrapCheck> sig;

    // Subquestion (c)
    // Connecting slots to the signal
    sig.connect(&slot1);
    sig.connect(&slot2);
    sig.connect(&slot3);

    bool result = sig();

    std::cout << "Combiner result: " << (result ? "true" : "false") << std::endl;

    return 0;
}
