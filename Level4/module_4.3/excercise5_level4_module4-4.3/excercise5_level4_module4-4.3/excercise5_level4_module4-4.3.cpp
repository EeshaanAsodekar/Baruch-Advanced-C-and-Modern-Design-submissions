#include <iostream>
#include <random>
#include <bitset>
#include <chrono>

// Subquestion (b) and (c)
// N-> number of bits
template<int N>
double setBitsRatio()
{
	// seed from std::chrono high-resolution clock
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	// random number engine: std::mt19937
	std::mt19937 eng(seed);

	// we are setting the integer type as usigned 64 bit integer
	std::independent_bits_engine<std::mt19937, N, uint64_t> g(eng);

	return(std::bitset<N>(g()).count());
}

int main()
{
	// Subquestion (a)
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 eng(seed);
	std::independent_bits_engine<std::mt19937, 10, uint64_t> g(eng);
	auto num = g();
	auto bset = std::bitset<10>(num);
	std::cout << "as int: " << num << " as bitset: " << bset << std::endl;

	// Subquestion (b) and (c)
	double count2 = 0.0,count8 = 0.0,count16 = 0.0,count64 = 0.0;

	// accumulating the number of set bits
	for (int i = 0; i < 100; ++i)
	{
		count2 += setBitsRatio<2>();
		count8 += setBitsRatio<8>();
		count16 += setBitsRatio<16>();
		count64 += setBitsRatio<64>();
	}

	double score2 = count2 /200.0;
	double score8 = count8 /800.0;
	double score16 = count16 /1600.0;
	double score64 = count64 /6400.0;

	std::cout << "Score at 2: " << score2 << 
		"\nscore at 8: " << score8 <<
		"\nscore at 16: " << score16 << 
		"\nscore at 64: " << score64;

	return 0;
}
