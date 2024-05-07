#pragma once

#include <algorithm>

// OptionData class code not given in excercise code snippets or in the attached zip files
// designing a basic class to satisfy the the fucntionality required
class OptionData
{
public:
	// Data Members:
	// Data members kept as public for simplicity
	// It is wrong to keep the data as public; but the code SDE class directly accesses it
	// all the relevant parameters/data for an option
	double K; // strike
	double T; // time to expiration
	double r; // interest rate
	double sig; // volatility (implied vol)
	double D; // dividend yeild
	int type; // option type

	// Relevant Fucntions:
	// Defining constructors
	// Default constuctor - inputing typical option parameters
	// call option with one year to exprity, $100 strike, no dividend, and vol of 10%
	OptionData() :
		K(100), T(1), r(0.05), sig(0.1), D(0.0), type(1) {}
	// Constructor with parameters - need it for main initilization
	OptionData(double K_, double T_, double r_,double sig_, double D_, int type_):
		K(K_), T(T_), r(r_), sig(sig_), D(D_), type(type_){}
	// Copy constructor
	OptionData(const OptionData & opt):
		K(opt.K), T(opt.T), r(opt.r), sig(opt.sig), D(opt.D), type(opt.type) {}

	// returns the payoff of a put and a call option
	// when the current price of the underlying is St
	double myPayOffFunction(double St) {
		if (type == 1) return std::max(St - K, 0.0);
		else return std::max(K - St, 0.0);
	}
};

