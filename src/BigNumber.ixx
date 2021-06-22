module;

#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <iostream>

export module BigNumber;

export template<typename T = unsigned char>
class Number
{

//private:
//	std::array<std::vector<T>, 2> digits{};
//	bool isNegative = false;
//	
public:
	Number(const char* value) : Number(std::string{ value }) {}

	Number(const std::string& value)
	{
		//bool offsetStart = (value[0] == '+' || ((value[0] == '-')? (isNegative = true, true) : false));
	
		//std::size_t decimalIndex = value.find('.');

		//if (decimalIndex == std::string::npos)
		//	decimalIndex = value.size();

		//stringParser(value, 0, (std::size_t)offsetStart, decimalIndex);
		//stringParser(value, 1, decimalIndex + 1, value.size());
		std::cout << "test" << "\n";
	}
};
	//
//private:
	//void stringParser(const std::string& value, std::size_t destination, std::size_t start, std::size_t end)
	//{
	//	unsigned char groupSum = 0;
	//	bool placeNext = false;

	//	for (std::size_t index = start; index < end; index++)
	//	{
	//		if (std::isdigit(value[index]))
	//			groupSum += (value[index] - '0') * (placeNext ? 10 : 1);
	//		else
	//			throw std::invalid_argument("value can only contain numbers,  a single decimal point and +/- at the beginning");

	//		if (placeNext)
	//		{
	//			digits[destination].push_back(groupSum);
	//			groupSum = 0;
	//		}
	//		placeNext = !placeNext;

	//		if (groupSum > 0)
	//			digits[destination].push_back(groupSum);
	//	}
	//}
//};






