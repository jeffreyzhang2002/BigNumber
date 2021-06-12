#include <iostream>
#include <string>

import BigNumber;


int main()
{
	//Number n = Rational{ "012345.678900" };
	
	unsigned int a = 1342543;
	Number n = Integer{ a };
	std::cout << "Parsed!" << "\n";
	std::cout << to_string_raw(n) << "\n";

	
	
	std::cin.get();
}