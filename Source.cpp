#include <iostream>
#include <string>
#include <tuple>

import BigNumber;

void print(const std::string& number)
{
	std::string returnString{ "" };

	for (std::size_t j = 0; j < number.size(); j++)	
		returnString += std::to_string(number[j]) + " ";

	std::cout << returnString << "\n";
}


int main()
{
	//Integer n{ "12345" };
	Rational b{ "13.8102" };

	Rational c{ "212.981" };
	
	//std::cout << to_string_raw(n) << "\n";
	std::cout << to_string_raw(b) << "\n";

	std::cout << to_string_raw(c) << "\n";

	std::cin.get();
}