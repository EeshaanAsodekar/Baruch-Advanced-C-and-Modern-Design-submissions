#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <queue>

using FunctionType = std::function<double(double)>;

class Command
{
private:
    long ID; // priority of command
    FunctionType algo;
public:
    Command(const FunctionType& algorithm, long priority)
        : algo(algorithm), ID(priority) {}

    void Execute(double x) {
        // Introduce delay to simulate a heavy algorithm
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << algo(x) << '\n';
    }

    int priority() const
    {
        return ID;
    }
};

int main()
{
    // Subquestion (a)
    // creating a comprator lambda fucntion, to compare two instances of class "Command"
    // higher priority popped first
    auto Command_comparator = [](Command cmd1_lhs, Command cmd2_rhs) {
        return cmd1_lhs.priority() < cmd2_rhs.priority();
        };


    // Subquestion (b)
    // creating instances of class Command
    Command cmd1([](double x) -> double {return x*0.025;}, 1);
    Command cmd2([](double x) -> double {return x*0.5;}, 2);
    Command cmd3([](double x) -> double {return x;}, 3);
    Command cmd4([](double x) -> double {return x*2;}, 4);
    Command cmd5([](double x) -> double {return x*3;}, 5);
    Command cmd6([](double x) -> double {return x*4;}, 6);
    Command cmd7([](double x) -> double {return x*5;}, 7);

    // Subquestion (c)
    // creating priority queue of Commands and inserting Command objects into it
    std::priority_queue<Command, std::vector<Command>, decltype(Command_comparator)> commandQ(Command_comparator);

    commandQ.push(cmd1);
    commandQ.push(cmd2);
    commandQ.push(cmd3);
    commandQ.push(cmd4);
    commandQ.push(cmd5);
    commandQ.push(cmd6);
    commandQ.push(cmd7);

    // Subquestion (d)
    // Executing the commands in the priority queue until it is empty
    double x_input = 2.0;
    
    std::cout << "\nExecuting each command in the priority queue until it is empty for intput x = 2.0\n";

    while (!commandQ.empty()) {
        Command cmd = commandQ.top();
        cmd.Execute(x_input);
        commandQ.pop();
    }

}

