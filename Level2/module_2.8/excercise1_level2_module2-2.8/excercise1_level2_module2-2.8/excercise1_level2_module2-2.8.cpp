#include <iostream>
#include <bitset>
#include <string>

int main()
{
    // Subquestion (a)
    std::cout << "Subquestion (a)\n";
    std::bitset<4> bitSet1(3ul);
    std::bitset<4> bitSet2(4ull);

    std::cout << bitSet1 << std::endl;
    std::cout << bitSet2 << std::endl;

    // Subqeustion (b)
    std::cout << "\nSubquestion (b)\n";
    constexpr int N = 10;
    std::string str = "10101111";
    std::bitset<N> bitSet3(str);
    int index = 3, num_bits = 3;
    std::bitset<N> bitSet4(str,index);

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
        std::bitset<12> b(bit_string);
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
    unsigned long long value2 = bitSet1.to_ullong();
    std::string stringValue = bitSet1.to_string();

    std::cout << "\nbitSet1: " << bitSet1 << std::endl;
    std::cout << "value: " << value << std::endl;
    std::cout << "value: " << value2 << std::endl;
    std::cout << "stringValue: " << stringValue << std::endl;

    // Subquestion (f)
    std::cout << "\nSubquestion (f)\n";
    std::cout << "\nbitSet1: " << bitSet1 << std::endl;
    std::cout << "bitSet2: " << bitSet2 << std::endl;

    std::cout << "Bitsets equal?: " << std::boolalpha;
    std::cout << (bitSet1 == bitSet2) << std::endl;
    std::cout << "BitSets not equal?: " << std::boolalpha;
    std::cout << (bitSet1 != bitSet2) << std::endl;

    return 0;
}
