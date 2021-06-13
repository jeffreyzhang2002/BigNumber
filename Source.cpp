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
	//Number n = Rational{ "012345.678900" };
	
	unsigned int val = 1342543;
	Number n = Integer{ val };
	
	/*std::cout << "Parsed!" << "\n";
	std::cout << to_string_raw(n) << "\n";*/

	char a = 99;
	char b = 99;
	char c = 99;
	char d = 99;

	char v = 99;
	char w = 99;
	char x = 99;
	char y = 99;
	char z = 99;

	std::string addend1{};
	addend1 += a;
	addend1 += b;
	addend1 += c;
	addend1 += d;

	std::string addend2{};
	addend2 += v;
	addend2 += w;
	addend2 += x;
	addend2 += y;
	addend2 += z;
	
	print(addend1);
	print(addend2);

	auto tuple = n.addSegment(addend1, addend2);

	print(std::get<0>(tuple));
	std::cout << (int) std::get<1>(tuple) << "\n";
	
	
	
	std::cin.get();
}