#include <iostream>
#include <bitset>
#include <functional>
#include <string>
#include <cstddef>
#include <iostream>

int main()
{
	// Subquestion (a)
	const int N = 5;
	std::bitset<N> bs1(std::string("11001"));
	std::bitset<N> bs2(std::string("10111"));

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


	// Subquestion (e)
	std::bitset<8> bs3("10101010");
	std::bitset<8> bs4("01010101");

	std::hash<std::string> hash_fn;

	size_t bs3_hash = hash_fn(bs3.to_string());
	size_t bs4_hash = hash_fn(bs4.to_string());

	std::cout << "Hash of bs3: " << bs3_hash << '\n';
	std::cout << "Hash of bs4: " << bs4_hash << '\n';

	// Subquestion (f)
	// Subquestion (g)
	std::byte b1{ 0b0011 }; // from a binary literal
	std::byte b2{ 3 }; // from an integer
	std::byte b3 = b1 & b2; // binary logical operator on existing bytes

	// Subquestion (h)
	std::byte b5{ 0b1100 };
	std::byte b6{ 0b1010 };

	std::byte result_and = b5 & b6; // AND operation
	std::byte result_or = b5 | b6; // OR operation

	// Subquestion (i)
	std::byte b{ 0b00001111 }; // Create a byte from a binary literal
	// we are shifting an 8 bit byte by 8 poisitions
	std::byte left_shifted = b << 8; // Left shift by 8 positions
	std::byte right_shifted = b >> 8; // Right shift by 8 positions
	// Since b is an 8 bit byte, these operations are trying to shift bits into non - existent positions, 
	// leading to undefined/extreme behavior.

	// Subquestion (j)
	/*
	* Memory Access: Bytes and bitsets can be used to manipulate raw memory.
	* 
	* Cryptography: In cryptographic algorithms, when data is manipulated at the bit level,
	* bytes and bitsets provide an efficient way to perform these manipulations.
	* 
	* Performance Improvements : Bitsets can provide significant memory savings and 
	* performance improvements when dealing with large sets of boolean values; 
	* can use bitsets instead of vectors or arrays of bool which have
	* lower performance for this use case.
	*/
	
	return 0;
}

