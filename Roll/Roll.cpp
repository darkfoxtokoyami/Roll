// Roll
//   A statistically average/uniform dice roller [c++11]
//
//  Fox Dark (2016-10-19)

#include <iostream>
#include <random>
#include <string>

void testRoll(int j)
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<> dis(1, 20);
	int stat[20] = { 0 };

	for (int i = 0; i < j; ++i)
		stat[(dis(gen) - 1)]++;

	std::cout << std::to_string(j) << ":\n";
	for (int i = 0; i < 20; ++i)
		std::cout << std::to_string(i + 1).c_str() << ": " << std::to_string(stat[i]).c_str() << "; " << std::to_string((float)(stat[i] * 100) / (float)j).c_str() << "%\n";

	return;
}

int roll(int dice, int dsize, int mod)
{
	// Random Generator
	std::random_device rd;
	std::mt19937_64 gen(rd());  // You may want to change this to std::mt19937 if you're compiling for 32-bit/x86
	std::uniform_int_distribution<> dis(1, dsize);	// This is the magic candy that makes our distribution uniform (obviously)

	int total = 0;
	int t = 0;
	std::string total_formula = "(";

	for (int i = 0; i < dice; ++i)
	{
		t = dis(gen);
		total_formula += std::to_string(t);
		total_formula += " + ";
		total += t;
	}

	total_formula = total_formula.substr(0, total_formula.length() - 3);
	total_formula += ")";

	if (mod > 0)
	{
		total_formula += " + ";
		total_formula += std::to_string(mod);
	}
	else if (mod < 0)
	{
		total_formula += " - ";
		total_formula += std::to_string(mod*-1);
	}

	total += mod;
	std::cout << std::to_string(total) << " ";	// Outputs dice roll
	std::cout << total_formula.c_str() << "\n"; // Outputs formula of dice roll
	return total;
}

int main(int argc, const char* argv[])
{
	/////////////////
	// Arg Parsing //
	/////////////////
	std::string arg;
	int dice = 0, dsize = 0, mod = 0, pos_d = 0, pos_p = 0, pos_m = 0;


	if (argc != 2)
	{
		std::cout << "Usage: roll xdy[+/-z]\n    X -> Number of dice.\n    Y -> Size of die\n    Z (Optional) -> Modifier to be added/subtracted from the total";
		exit(1);
	}

	// Get the arg
	arg = std::string(argv[1]);

	// Don't run find a bunch of times
	//std::cout<<std::to_string(arg.find('d'));
	pos_d = arg.find('d');
	pos_p = arg.find('+');
	pos_m = arg.find('-');

	// Parse the arg input for the numbers we want
	if (pos_d != std::string::npos)
	{
		dice = std::stoi(arg.substr(0, pos_d));  //This is the same regardless of if there's a + or - present

		if (pos_p != std::string::npos)         // xdy+z
		{
			mod = std::stoi(arg.substr(pos_p));
			dsize = std::stoi(arg.substr(pos_d + 1, pos_p - pos_d));
		}
		else if (pos_m != std::string::npos)    // xdy-z
		{
			mod = std::stoi(arg.substr(pos_m));
			dsize = std::stoi(arg.substr(pos_d + 1, pos_m - pos_d));
		}
		else                                    // xdy
			dsize = std::stoi(arg.substr(pos_d + 1));
	}
	/////////////////////
	// End Arg Parsing //
	/////////////////////

	roll(dice, dsize, mod);
	return 0;
}