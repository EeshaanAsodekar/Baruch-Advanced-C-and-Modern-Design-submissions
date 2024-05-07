#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <random>

int main()
{
	auto printVec = [](std::vector<int> vec) -> void {
		for_each(vec.begin(), vec.end(), [](int x)->void {std::cout << x << "\t";});
		};

	std::vector<int> vec{ 1,2,3,4,5,6,7,8,9,10};

	std::cout << "vec:" << std::endl;
	printVec(vec);

	//a) Scale all values by a given factor.
	//  transform - Modifying
	int factor = 2;
	std::vector<int> vec_a(vec.size());
	std::transform(vec.begin(), vec.end(), vec_a.begin(),[&](int x)->int {return x * factor;});
	std::cout << "\nvec_a:" << std::endl;
	printVec(vec_a);

	//b) Count the number of elements whose values are in a given range.
	//	count_if - Non Modifying
	int upperBound = 1, lowerBound = 3;
	int numEle = std::count_if(vec.begin(), vec.end(), [=](int x) {return x > upperBound && x <= lowerBound;});
	std::cout << "\nnumEle:"  << numEle << std::endl;

	//c) Find the average, minimum and maximum values in a container.
	//	min_element and max_element - Non Modifying; average: accumulate()/mylist.size() - Numeric
	
	std::cout << "\nvec min: " << *std::min_element(vec.begin(), vec.end()) << std::endl;
	std::cout << "\nvec max: " << *std::max_element(vec.begin(), vec.end()) << std::endl;
	std::cout << "\nvec avg: " << (std::accumulate(vec.begin(),vec.end(), 0)+0.0)/vec.size() << std::endl;
	
	//d) Find the first element that is (that is not) in a range.
	//	find_if or find_if_not: Non modifying
	
	std::cout << "\nfirst even: " << *std::find_if(vec.begin(), vec.end(), [](int x)->bool {return x % 2 == 0;});

	//e) Search for all occurrences of ‘3456’ in the container.
	// Non Modifying
	// loop till pos != mylist.end() and use std::search to get the position of the subrange
	
	std::vector<int> searchMe{ 3,4,5,6 };
	auto itr = std::search(vec.begin(), vec.end(), searchMe.begin(),searchMe.end());
	while (itr != vec.end()) {
		std::cout << "\nsequence occurence at:" << std::distance(vec.begin(), itr) << "\t";
		itr = std::search(++itr, vec.end(), searchMe.begin(), searchMe.end());
	}

	//f) Determine if the elements in two ranges are equal.
	//	equal() - non-modifying
	
	std::vector<int> vec_f{ 1,2,3,4,5,6,7,8,9,10 };
	std::cout << "\nare vec and vec_f equal ranges: " << std::boolalpha << std::equal(vec.begin(), vec.end(), vec_f.begin());
	
	//g) Determine if a set is some permutation of ‘12345’.
	//	is_permutation() - non-modifying
	
	std::vector<int> referenceSet = { 10,9,8,7,6,5,4,3,2,1 };
	std::cout << "\nis referenceSet a permutation of vec: " << std::boolalpha << std::is_permutation(vec.begin(), vec.end(), referenceSet.begin());


	//h) Is a container already sorted?
	//	is_sorted - Non modifying
	
	std::cout << "\nis vec sorted: " << std::boolalpha << std::is_sorted(vec.begin(), vec.end());

	//i) Copy a container into another container.
	//	copy - modifying
	
	std::vector<int> vec_i(vec.size());

	std::copy(vec.begin(), vec.end(), vec_i.begin());
	std::cout << "\nvec_i: " << std::endl;
	printVec(vec_i);

	//j) Move the last 10 elements of a container to the front.
	//	rotate - mutating algorithms

	std::cout << "\nvec: " << std::endl;
	printVec(vec_i);
	std::rotate(vec_i.begin(), vec_i.end() - 3, vec_i.end());
	std::cout << "\nvec after rotation: " << std::endl;
	printVec(vec_i);

	//k) Swap two ranges at a given position.
	//	swap_ranges - modifying
	
	std::swap_ranges(vec_i.begin(), vec_i.begin() + 2, vec_i.begin() + 3);
	std::cout << "\nvec after swapping ranges: " << std::endl;
	printVec(vec_i);

	//l) Generate values in a container based on some formula.
	//	generate - mutating
	std::vector<int> vec_l(vec.size());
	std::generate(vec_l.begin(), vec_l.end(), []() { return std::rand(); });
	std::cout << "\nvec_l after rand() generation: " << std::endl;
	printVec(vec_l);

	//m) Replace all uneven numbers by zero.
	//	replace_if - modifying
	
	std::replace_if(vec_l.begin(), vec_l.end(), [](int x) {return x % 2 != 0;}, 0);
	std::cout << "\nvec_l after replace_if: " << std::endl;
	printVec(vec_l);

	//n) Remove all elements whose value is less than 100.
	//	remove_if - modifying
	std::vector<int> vec_n{ 101,102,3,104,107,2005 };
	std::remove_if(vec_n.begin(), vec_n.end(), [](int x) {return x < 100;});
	std::cout << "\nvec_n after remove_if: " << std::endl;
	printVec(vec_n);

	//o) Shuffle a container randomly (pre- and post-C++11 versions).
	//	shuffle - mutating
	std::random_shuffle(vec_n.begin(), vec_n.end()); // Pre-C++11
	std::cout << "\nvec_n after random_shuffle: " << std::endl;
	printVec(vec_n);
	std::shuffle(vec_n.begin(), vec_n.end(), std::default_random_engine{}); // Post-C++11
	std::cout << "\nvec_n after shuffle: " << std::endl;
	printVec(vec_n);

	//p) Compute one-sided divided differences of the values in a container.
	//	adjacent difference - numeric algos
	std::vector<int> vec_adjDiff(vec_n.size());
	std::adjacent_difference(vec_n.begin(), vec_n.end(), vec_adjDiff.begin());
	std::cout << "\vec_adjDiff after adjacent_difference on vec_n: " << std::endl;
	printVec(vec_adjDiff);

    return 0;
}
