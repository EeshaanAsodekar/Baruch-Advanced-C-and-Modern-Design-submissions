#include <iostream>
#include <queue>
#include <deque>

int main()
{
    // Subquestion (a)
    std::priority_queue <long long> priorityQ;


    std::cout << "\nPushing 66,22,44 onto the priorityQ " << std::endl;
    priorityQ.push(66);
    priorityQ.push(22);
    priorityQ.push(44);

    
    std::cout << "\nTop Element: " << priorityQ.top() << std::endl;
    std::cout << "\nprev size: " << priorityQ.size() << std::endl;
    std::cout << "\npopping element " << std::endl;
    priorityQ.pop();
    std::cout << "\ncurr size: " << priorityQ.size() << std::endl;


    std::cout << "\nPushing 11,22,33 onto the priorityQ " << std::endl;
    priorityQ.push(11);
    priorityQ.push(22);
    priorityQ.push(33);


    std::cout << "\nprev size: " << priorityQ.size() << std::endl;
    std::cout << "\npopping element " << std::endl;
    priorityQ.pop();
    std::cout << "\ncurr size: " << priorityQ.size() << std::endl;
    

    std::cout << "\nIterating over priorityQ: " << std::endl;
    while (priorityQ.size() != 0) {
        std::cout << priorityQ.top() << " ";
        priorityQ.pop();
    }
    // Output-> 33 22 22 11


    // yes, the output is consistent with the expectations;
    // the largest number is removed each time we pop the priotity queue,
    // and the largest number is returned when we do .top() on the queue.
    // This is because the default comparator is std::less

    // Subquestion (b)
    std::priority_queue<long long, std::deque<long long>, std::greater<long long>> priorityQ_2;

    std::cout << "\n----------------------------------------------------------------------\n";
    std::cout << "\n\nSubquestion (b) output:\n";
    std::cout << "\nPushing 66,22,44 onto the priorityQ_2 " << std::endl;
    priorityQ_2.push(66);
    priorityQ_2.push(22);
    priorityQ_2.push(44);


    std::cout << "\nTop Element: " << priorityQ_2.top() << std::endl;
    std::cout << "\nprev size: " << priorityQ_2.size() << std::endl;
    std::cout << "\npopping element " << std::endl;
    priorityQ_2.pop();
    std::cout << "\ncurr size: " << priorityQ_2.size() << std::endl;


    std::cout << "\nPushing 11,22,33 onto the priorityQ_2 " << std::endl;
    priorityQ_2.push(11);
    priorityQ_2.push(22);
    priorityQ_2.push(33);


    std::cout << "\nprev size: " << priorityQ_2.size() << std::endl;
    std::cout << "\npopping element " << std::endl;
    priorityQ_2.pop();
    std::cout << "\ncurr size: " << priorityQ_2.size() << std::endl;


    std::cout << "\nIterating over priorityQ_2: " << std::endl;
    while (priorityQ_2.size() != 0) {
        std::cout << priorityQ_2.top() << " ";
        priorityQ_2.pop();
    }

    // Output-> 22 33 44 66

    // since we changed the 'Class Compare' of the std::priority_queue from std::less to std::greater
    // the policy of element removal and priority was reversed.
    // In this case, the smaller elements are removed first (highest priority of deletion)

    // Subquestion (c)

    // defining a bespoke comparison lambda fucntion
    // element with the lowest number of factors of 2 is highest priority
    auto bespoke_comparison_function = [](long long x, long long y) {
        auto countFactorsOfTwo = [](long long n) -> long long {
            long long count = 0;
            while (n % 2 == 0) {
                n /= 2;
                count++;
            }
            return count;
            };
        return countFactorsOfTwo(x) > countFactorsOfTwo(y);
        };

    std::priority_queue<long long, std::deque<long long>, decltype(bespoke_comparison_function)> priorityQ_3(bespoke_comparison_function);

    std::cout << "\n----------------------------------------------------------------------\n";
    std::cout << "\n\nSubquestion (c) output:\n";
    std::cout << "\nPushing 66,22,44 onto the priorityQ_3 " << std::endl;
    priorityQ_3.push(66);
    priorityQ_3.push(22);
    priorityQ_3.push(44);


    std::cout << "\nTop Element: " << priorityQ_3.top() << std::endl;
    std::cout << "\nprev size: " << priorityQ_3.size() << std::endl;
    std::cout << "\npopping element " << std::endl;
    priorityQ_3.pop();
    std::cout << "\ncurr size: " << priorityQ_3.size() << std::endl;


    std::cout << "\nPushing 11,22,33 onto the priorityQ_3 " << std::endl;
    priorityQ_3.push(11);
    priorityQ_3.push(22);
    priorityQ_3.push(33);


    std::cout << "\nprev size: " << priorityQ_3.size() << std::endl;
    std::cout << "\npopping element " << std::endl;
    priorityQ_3.pop();
    std::cout << "\ncurr size: " << priorityQ_3.size() << std::endl;


    std::cout << "\nIterating over priorityQ_3: " << std::endl;
    while (priorityQ_3.size() != 0) {
        std::cout << priorityQ_3.top() << " ";
        priorityQ_3.pop();
    }

    // Output-> 33 22 22 44

    // the output of this subquestion is as desired
    // the bespoke_comparison_function is designed such that we remove the 
    // elements with the least number of factors of 2.
    // This expectation is met when testing the priorityQ_3

    return 0;
}
