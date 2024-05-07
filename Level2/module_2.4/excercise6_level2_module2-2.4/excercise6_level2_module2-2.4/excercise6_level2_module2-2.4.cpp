#include <iostream>
#include <memory>

int main()
{
	// Subquestion (a)
	std::shared_ptr<double> commonValue(new double(3.1415));
	std::cout << "Ref count of commonValue after declaring and initilizing the commonValue shared_ptr: " << commonValue.use_count() << std::endl; //1
	// value = 1

	std::weak_ptr<double> w_ptr;
	w_ptr = commonValue; // weak pointer assigned to shared pointer
	std::cout << "Ref count of commonValue after initializing the weak_ptr 'w_ptr' to observe the shared_ptr commonValue: " << commonValue.use_count() << std::endl; //1
	// value still = 1

	// checking if the weak pointer assigned to the strong pointer is empty
	// it isn't
	if (w_ptr.expired())
	{
		std::cout<< "weak_ptr 'w' has no associated resource " << std::endl;
	}
	else
	{
		std::cout<< "weak_ptr 'w' has associated resource " << std::endl;
	}

	// Subquestion (c)
	std::weak_ptr<double> w_ptr2;
	w_ptr2 = w_ptr;
	std::cout << "Ref count of commonValue after assigning \"w_ptr2 = w_ptr\" : " << commonValue.use_count() << std::endl; 
	//  count = 1

	std::cout << "w_ptr Ref count after assigning \"w_ptr2 = w_ptr\" : " << w_ptr.use_count() << std::endl;
	

	std::shared_ptr<double> commonValue2(w_ptr);
	std::cout<< "Ref count of commonValue2 after declaring and initilizing another shared_ptr commonValue2" <<
		" and assigning it to another weak pointer w_ptr2 :" << commonValue2.use_count() << std::endl;
	// count = 2

	std::cout << "w_ptr Ref count after using it to initialize another shared_ptr commonValue2: " << w_ptr.use_count() << std::endl;
	
	/*
	* std::weak_ptr also has a use_count() function. 
	* This function returns the number of std::shared_ptr instances sharing the ownership of 
	* the managed object at the instant of the call.
	*/

	return 0;
}


