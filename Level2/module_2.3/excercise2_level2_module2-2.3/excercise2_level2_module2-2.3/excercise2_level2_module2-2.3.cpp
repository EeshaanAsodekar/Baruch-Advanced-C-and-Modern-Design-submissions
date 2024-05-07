#include <iostream>
#include <vector>
#include <array>
#include <functional>

int main()
{
	// Subquestion (a)
    std::cout << "Subquestion (a)\n\n";
    int size = 4; double val = 2.71;
    std::vector<double> data(size, val);

    // Default capture mode (not preferred)
    auto fun = [data = std::move(data)]() mutable
        {
            for (std::size_t i = 0; i < data.size(); ++i)
            {
                data[i] = 3.14; std::cout << data[i] << ",";
            }
            std::cout << '\n';
        };

    fun();

    std::cout << "size of data after fun() has been called: " << data.size() << std::endl;

    // 'data' is blank!; it has been moved from
    for (std::size_t i = 0; i < data.size(); ++i)
    {
        data[i] = 3.14; std::cout << data[i] << ":";
    }



    // Subquestion (b)
    std::cout << "\n\n\nSubquestion (b)\n\n";
    int x = 1'000'000; // This is a digit separator
    auto fun4 = [&r = x]()
        {
            r *= 2;
            std::cout << "\nr: " << r;
        };

    // exprimenting with function calls and how the value of r is affected
    // Calling the lambda function once
    fun4();  

    // Calling the lambda function again to see if 'r' retains its value
    fun4();

    // Changing the value of 'x' and see if it affects 'r'
    x = 500'000;
    fun4();



    // Subquestion (c)
    std::cout << "\n\n\nSubquestion (c)\n\n" ;
    int size2 = 3; double val2 = 1.41;
    std::vector<double> data2(size2, val2);
    std::array<double, 3> data3 = { 1.2, 2.4, 4.7 };

    // converting stored lambda fucntion from the std::bind C++11 approach 
    // to the init capture/generalized capture approach of C++14
    // functionality same as before; but the funtions code is far more readable
    auto fun3 = [array = std::move(data2), array2 = std::move(data3)]() mutable
        {
            for (std::size_t i = 0; i < array.size(); ++i)
            {
                array[i] = 3.14; std::cout << array[i] << "/";
            }
            std::cout << '\n';
            for (std::size_t i = 0; i < array2.size(); ++i)
            {
                array2[i] = 2.71; std::cout << array2[i] << "/";
            }

        };

    fun3();

    if (0 == data2.size() || 0 == data3.size())
    {
        std::cout << "\nDouble arrays have no elements, OK\n";
    }
    else
    {
        std::cout << "\n Ouch!\n";
        for (std::size_t i = 0;i < data2.size(); ++i)
        {
            std::cout << data2[i] << "^";
        }
        for (std::size_t i = 0; i < data3.size(); ++i)
        {
            std::cout << data3[i] << "^";
        }
    }

	return 0;
}
