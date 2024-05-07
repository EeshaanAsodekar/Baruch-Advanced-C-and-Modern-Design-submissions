#include <bitset>
#include <iostream>
#include <array>

/*
* Subquestion (a)
* The design choice of choosing the std::array<std::bitset<M>, N> was made by taking into account these factors:
* 1) it makes the matrix interface more intutive to work with
* 2) code is easier to read and debug
* 3) can directly us the operator overloading from std::bitset, no need to define excruciating functions
* 4) the other approach did use slightly less memory, but the aforementioned advantages outwieghed it
*/

template <std::size_t N, std::size_t M>
class BitMatrix {
public:
    // default constructor
    BitMatrix() : data() {}

    // set/reset all bits
    void set() { for (auto& row : data) row.set(); }
    void reset() { for (auto& row : data) row.reset(); }

    // flip the bits
    void flip() { for (auto& row : data) row.flip(); }

    // test if none, all or any bits are set
    bool none() const { for (const auto& row : data) if (row.any()) return false; return true; }
    bool all() const { for (const auto& row : data) if (!row.all()) return false; return true; }
    bool any() const { for (const auto& row : data) if (row.any()) return true; return false; }

    // access the elements
    std::bitset<M>& operator[] (int index) { return data.at(index); }
    const std::bitset<M>& operator[] (int index) const { return data.at(index); }

    // count the number of set bits
    std::size_t count() const { std::size_t count = 0; for (const auto& row : data) count += row.count(); return count; }

    // boolean operations on bit matrices
    BitMatrix<N, M> operator&(const BitMatrix<N, M>& other) const {
        BitMatrix<N, M> result;
        for (std::size_t i = 0; i < N; ++i) result[i] = data[i] & other[i];
        return result;
    }

    BitMatrix<N, M> operator|(const BitMatrix<N, M>& other) const {
        BitMatrix<N, M> result;
        for (std::size_t i = 0; i < N; ++i) result[i] = data[i] | other[i];
        return result;
    }

    BitMatrix<N, M> operator^(const BitMatrix<N, M>& other) const {
        BitMatrix<N, M> result;
        for (std::size_t i = 0; i < N; ++i) result[i] = data[i] ^ other[i];
        return result;
    }

    void printBitMatrix() const {
        for (auto row : data) {
            std::cout << row << std::endl;
        }
    }

private:
    std::array<std::bitset<M>, N> data;
};


#include <iostream>

int main() {
    // create a BitMatrix
    BitMatrix<3, 4> bm1;
    bm1[0] = std::bitset<4>("1010");
    bm1[1] = std::bitset<4>("1100");
    bm1[2] = std::bitset<4>("0110");

    std::cout << "the matrix bm1 is: " << std::endl;
    bm1.printBitMatrix();

    // test set/reset/flip functions
    bm1.set();
    std::cout << "\nSET: " << std::endl;

    bm1.printBitMatrix();

    bm1.reset();
    std::cout << "\nRESET: " << std::endl;
    bm1.printBitMatrix();

    bm1.flip();
    std::cout << "\nFLIP: " << std::endl;
    bm1.printBitMatrix();

    // test none/all/any functions
    std::cout << "None: " << bm1.none() << std::endl;
    std::cout << "All: " << bm1.all() << std::endl;
    std::cout << "Any: " << bm1.any() << std::endl;

    // test count function
    std::cout << "Count: " << bm1.count() << std::endl;

    // create another BitMatrix
    BitMatrix<3, 4> bm2;
    bm2[0] = std::bitset<4>("1100");
    bm2[1] = std::bitset<4>("1010");
    bm2[2] = std::bitset<4>("1001");

    std::cout << "\n\nthe matrix bm2 is: " << std::endl;
    bm2.printBitMatrix();

    // test Boolean operations
    BitMatrix<3, 4> bm_and = bm1 & bm2;
    BitMatrix<3, 4> bm_or = bm1 | bm2;
    BitMatrix<3, 4> bm_xor = bm1 ^ bm2;

    std::cout << "\nAND: " << std::endl;
    bm_and.printBitMatrix();

    std::cout << "\nOR: " << std::endl;
    bm_or.printBitMatrix();

    std::cout << "\nXOR: " << std::endl;
    bm_xor.printBitMatrix();

    return 0;
}
