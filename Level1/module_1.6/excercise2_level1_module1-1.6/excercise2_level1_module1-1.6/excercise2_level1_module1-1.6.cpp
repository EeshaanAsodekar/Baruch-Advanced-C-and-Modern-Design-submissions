#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

// given 
using InputFunction = function<double()>;
using OutputFunction = function<void(const std::vector<double>&)>;

class TMPClass final{
private:
	vector<double> vec;
	InputFunction input_function;
	OutputFunction output_function;
	

public:
	TMPClass(size_t n, double startValue, InputFunction input_function_, OutputFunction output_function_) :
		input_function(input_function_), output_function(output_function_) {
		for (int i = 0;i < n;i++) vec.push_back(startValue);
	}

	void run_algorithm() {

		// Preprocessor
		auto factor = input_function();

		// Computation
		transform(vec.begin(), vec.end(), vec.begin(), [&](const double& x)->double {return x * factor;});

		// Postprocessor
		output_function(vec);
	}
};

int main()
{
	InputFunction input_function = []() -> double {return 4.0;};
	
	OutputFunction output_function = [](const vector<double>& vec) ->void {
		for (auto elem : vec) {
			cout << elem << " ";
		}
		};

	double ele = 1.0;
	int size = 3;
	TMPClass TMPClass_object(size,ele, input_function,output_function);

	// just for printing out to the console
	for (int i = 0;i < size;i++) {
		cout << ele << " ";
	}
	cout << endl;

	cout << "factor: " << input_function() << endl;

	// running the algorithm
	TMPClass_object.run_algorithm();

	return 0;
}
