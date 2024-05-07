#include <ratio>
#include <iostream>

int main() {
    // Subquestion (a) Create a number of instances of std::ratio and print them.
    std::ratio<2, 3> r1;
    std::ratio<3, 4> r2;
    std::ratio<5, 6> r3;

    std::cout << "r1: " << r1.num << "/" << r1.den << "\n";
    std::cout << "r2: " << r2.num << "/" << r2.den << "\n";
    std::cout << "r3: " << r3.num << "/" << r3.den << "\n";

    // Subquestion (b) Create two std::ratio instances; add, subtract, multiply and divide them.
    typedef std::ratio_add<std::ratio<2, 3>, std::ratio<3, 4>>::type result_add;
    typedef std::ratio_subtract<std::ratio<2, 3>, std::ratio<3, 4>>::type result_subtract;
    typedef std::ratio_multiply<std::ratio<2, 3>, std::ratio<3, 4>>::type result_multiply;
    typedef std::ratio_divide<std::ratio<2, 3>, std::ratio<3, 4>>::type result_divide;

    std::cout << "r1 + r2: " << result_add::num << "/" << result_add::den << "\n";
    std::cout << "r1 - r2: " << result_subtract::num << "/" << result_subtract::den << "\n";
    std::cout << "r1 * r2: " << result_multiply::num << "/" << result_multiply::den << "\n";
    std::cout << "r1 / r2: " << result_divide::num << "/" << result_divide::den << "\n";

    return 0;
}
