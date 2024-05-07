#include <iostream>
#include "Matrix.h"
#include "Proposition.h"

using value_type = Proposition;
template <int NR, int NC>
using BitMap = Matrix<value_type, NR, NC>;
template <int NR, int NC>
using BitMap2 = std::array<std::bitset<NC>, NR>;

// Subquestion (a)
// free print fucntions correponding to BitMap and BitMap2
template <int NR, int NC>
void print_BitMap(BitMap<NR, NC> map) {
    for (int i = 0; i < NR; i++) {
        for (int j = 0; j < NR; j++) {
            map(i, j).print();
            std::cout << "\t";
        }
        std::cout << "\n";
    }
}

template <int NR, int NC>
void print_BitMap2(BitMap2<NR, NC> map) {
    for (auto row : map) {
        for (int j = 0; j < NC; j++) {
            std::cout << row[j] << "\t";
        }
        std::cout << "\n";
    }
}

// Subquestion (c) - initialise fucntion for rows of BitMap2
template <int NR, int NC>
void initialise(BitMap2<NR, NC>& map, int rowNumber, const std::string& str) {
    if (str.size() == NC) {
        map[rowNumber] = std::bitset<NC>(str);
    }
    else { // string input to initialise in incorrect
        std::cout << "incorrect string input" << std::endl;
    }

}

// Subquestion (b)
using BitFunction = std::function <Proposition(const Proposition&,
    const Proposition&)>;

template <int NR, int NC>
BitMap<NR, NC> mask(BitMap<NR, NC> bm1,
    BitMap<NR, NC> bm2,
    BitFunction masker) {
    BitMap<NR, NC> result;

    for (int i = 0; i < NR; i++) {
        for (int j = 0; j < NC; j++) {
            result(i, j) = masker(bm1(i, j), bm2(i, j));
        }
    }
    return result;
}

int main()
{
    // Subquestion (a)
    BitMap<3, 3> bitmap1(1);
    BitMap2<3,3> bitmap2;

    std::cout << "bitmap1:\n";
    print_BitMap(bitmap1);
    std::cout << "\nbitmap2:\n";
    print_BitMap2(bitmap2);

    // Subquestion (b)
    BitMap<5, 5> bm1(true);
    bm1(4, 3) = false;

    BitMap<5, 5> bm2(false);
    bm2(4, 3) = true;

    std::cout << "\n\nbm1:\n";
    print_BitMap(bm1);
    std::cout << "\nbm2:\n";
    print_BitMap(bm2);

    // testing all the boolean operators
    auto AND = [](const Proposition& p1, const Proposition& p2) { return p1 & p2; };
    auto OR = [](const Proposition& p1, const Proposition& p2) { return p1 | p2; };
    auto XOR = [](const Proposition& p1, const Proposition& p2) { return p1 ^ p2; };
    auto CONDITIONAL = [](const Proposition& p1, const Proposition& p2) { return p1 % p2; };
    auto BICONDITIONAL = [] (const Proposition& p1, const Proposition& p2) { return p1 * p2; };

    auto bm1_AND_bm2 = mask(bm1, bm2, AND);
    std::cout << "\nbm1 AND bm2:\n";
    print_BitMap(bm1_AND_bm2);

    auto bm1_OR_bm2 = mask(bm1, bm2, OR);
    std::cout << "\nbm1 OR bm2:\n";
    print_BitMap(bm1_OR_bm2);

    auto bm1_XOR_bm2 = mask(bm1, bm2, XOR);
    std::cout << "\nbm1 XOR bm2:\n";
    print_BitMap(bm1_XOR_bm2);

    auto bm1_COND_bm2 = mask(bm1, bm2, CONDITIONAL);
    std::cout << "\nbm1 COND bm2:\n";
    print_BitMap(bm1_COND_bm2);

    auto bm1_BCOND_bm2 = mask(bm1, bm2, BICONDITIONAL);
    std::cout << "\nbm1 BCOND bm2:\n";
    print_BitMap(bm1_BCOND_bm2);

    // NOTE: we had to implement the operator& , operator| , and operator^ 
    // as friends of the Proposition class; just the way we had for operator% and operator*
    // in excercise 1.


    // Subquestion (c)
    BitMap<7, 7> bitblt(false);
    bitblt(1, 2) = bitblt(1, 3) = bitblt(1, 4) = bitblt(1, 6) = true;

    std::cout << "\n\nbitblt:\n";
    print_BitMap(bitblt);

    const int P = 8;
    const int Q = 8;
    BitMap2<P, Q> bitblt2;
    // created initialise fucntion to set the rows for BitMap2 
    initialise(bitblt2, 0, "10101010");
    std::cout << "\n\nbitblt2:\n";
    print_BitMap2(bitblt2);

    /* Comparison of the two classes
    - BitMap provides a more abstract and high-level interface, which can make it easier to use for complex operations
    - We have built significant fucntionality in the Matrix class and that fucntionality can be readily used for BitMap
    - But we need to write more boilerplate code and there is more overhead because of Matrix and Preposition classes

    - On the other hand BitMap2 is a lower level data structure with more direct interface
    - It is built on top of the stl std::array and and std::bitset
    - Because it being built using stl containers, it is plausible that is would be more efficient that BitMap
    - But at the same time, we have defined a lot of functionality for Matrix and Preposition, which can make
      implementation of complex fucntions easier in BitMap than BitMap2
    - Additionally, initializing BitMap is more painful than BitMap2, but we can simply define a custom fucntion 
      in the Matrix class to remedy this as well

    Thus, because of our custom defined functionality of the Matrix and Preposition classes, BitMap is easier 
    to work with when implemting complex fucntionality; while in the case of BitMap2 we'll have to start from scratch
    if we want to define any complex operations.    
    */

    return 0;
}
