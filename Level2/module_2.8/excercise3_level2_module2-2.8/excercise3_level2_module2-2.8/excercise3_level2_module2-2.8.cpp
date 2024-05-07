#include <iostream>
#include <boost/dynamic_bitset.hpp>

int main()
{
    // Subquestion (b)
    boost::dynamic_bitset<> x(5, 17);
    std::cout << x << std::endl;

    x.resize(3);
    std::cout << x << std::endl;

    x.push_back(1);
    std::cout << x << std::endl;

    x.pop_back();
    std::cout << x << std::endl;

    x.clear();
    std::cout << x << std::endl;

    // Subquestion (c)
    boost::dynamic_bitset<> dbs1(4, 3);
    boost::dynamic_bitset<> dbs2(4, 2);

    std::cout << "\ndbs1: " << dbs1 << std::endl;
    std::cout << "dbs2: " << dbs2 << std::endl;

    bool is_subset = ((dbs1 & dbs2) == dbs2);
    std::cout << "dbs2 is a subset of dbs1: " << std::boolalpha << is_subset << '\n';

    // Subquestion (d)
    boost::dynamic_bitset<> dbs3(7,81);

    std::cout << "\ndbs3: " << dbs3 << std::endl;

    // find the first set bit
    boost::dynamic_bitset<>::size_type i = dbs3.find_first();
    std::cout << "First set bit: " << i << '\n';

    // find the next set bit
    i = dbs3.find_next(i);
    std::cout << "Next set bit: " << i << '\n';

    std::cout << "\n\n\nOutput of the ported code from excercise 1 and 2: \n";


    // Subquestion (a)
    // Excercise 1/ Question 1 ported code
    // Subquestion(a)
    std::cout << "Subquestion (a)\n";
    boost::dynamic_bitset<> bitSet1(4,3ul);
    boost::dynamic_bitset<> bitSet2(4,4ull);

    std::cout << bitSet1 << std::endl;
    std::cout << bitSet2 << std::endl;

    // Subqeustion (b)
    std::cout << "\nSubquestion (b)\n";
    int N = 10;
    std::string str = "10101111";
    boost::dynamic_bitset<> bitSet3(str);
    int index = 3, num_bits = 3;
    boost::dynamic_bitset<> bitSet4(str, index);

    std::cout << bitSet3 << std::endl;
    std::cout << bitSet4 << std::endl;

    // Subquestion (c)
    std::cout << "\nSubquestion (c)\n";

    try {
        std::string bit_string = "0101010101010"; // 13-bit string
        std::size_t bitset_size = 12; // 12-bit bitset

        if (bit_string.size() > bitset_size) {
            throw std::out_of_range("Bit string is too long for the bitset size.");
        }

        for (char c : bit_string) {
            if (c != '0' && c != '1') {
                throw std::invalid_argument("Invalid bit string. Bits should be either 0 or 1.");
            }
        }
        boost::dynamic_bitset<> b(bit_string);
        std::cout << "Bitset: " << b << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    // Subquestion (d)
    std::cout << "\nSubquestion (d)\n";

    bitSet4.set();
    std::cout << bitSet4 << std::endl;
    bitSet4.reset();
    std::cout << bitSet4 << std::endl;
    bitSet4.flip();
    std::cout << bitSet4 << std::endl;

    std::cout << "bitset\t" << "all\t" << "any\t" << "none\n" << bitSet1 << '\t'
        << bitSet1.all() << '\t' << bitSet1.any() << '\t' << bitSet1.none() << '\n';

    for (int i = 0;i < bitSet1.size();i++) {
        std::cout << bitSet1[i] << " ";
    }

    std::cout << "\ncount: " << bitSet1.count() << std::endl;

    // Subquestion (e)
    std::cout << "\nSubquestion (e)\n";
    unsigned long value = bitSet1.to_ulong();

    std::cout << "\nbitSet1: " << bitSet1 << std::endl;
    std::cout << "value: " << value << std::endl;

    // Subquestion (f)
    std::cout << "\nSubquestion (f)\n";
    std::cout << "\nbitSet1: " << bitSet1 << std::endl;
    std::cout << "bitSet2: " << bitSet2 << std::endl;

    std::cout << "Bitsets equal?: " << std::boolalpha;
    std::cout << (bitSet1 == bitSet2) << std::endl;
    std::cout << "BitSets not equal?: " << std::boolalpha;
    std::cout << (bitSet1 != bitSet2) << std::endl;

    // Excercise 2/ Question 2 ported code
    // Subquestion (a)
    N = 5;
    boost::dynamic_bitset<> bs1(N, 24ul);
    boost::dynamic_bitset<> bs2(N, 23ul);

    // Subquestion (b)
    bs1.flip();
    bs2.flip();

    // Subquestion (c)
    std::cout << "\nbs1: " << bs1 << std::endl;
    std::cout << "\nbs2: " << bs2 << std::endl;

    bs1 ^= bs2; // XOR 
    std::cout << "\nbs1 XOR bs2: " << bs1 << std::endl;

    bs1 != bs2; // Bitwise OR
    std::cout << "\nbs1 OR bs2: " << bs1 << std::endl;

    bs1 &= bs2; // Bitwise AND
    std::cout << "\nbs1 AND bs2: " << bs1 << std::endl;

    // Subquestion (d)
    std::cout << "bs1 Shifted left by 1: " << (bs1 << 1) << std::endl;
    std::cout << "bs1 Shifted right by 1: " << (bs1 >> 1) << std::endl;
    /*std::cout << "bs2 Shifted left by 1: " << (bs2 << 1) << std::endl;
    std::cout << "bs2 Shifted right by 1: " << (bs2 >> 1) << std::endl;*/

    
    return 0;
}
