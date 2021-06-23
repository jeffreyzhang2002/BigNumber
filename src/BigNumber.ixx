module;

#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <iostream>

export module BigNumber;

export template<typename T>
concept UnsignedIntegralType = std::is_integral<T>::value && !std::is_signed<T>::value;

export template<UnsignedIntegralType T = unsigned char>
class Number
{
	friend std::string to_string_raw(const Number<T>& number)
	{
		std::string returnString{ "Number format: \n" };

		for (std::size_t index = 0; index < number.digits[0].size(); index++)
			returnString += std::to_string(number.digits[0][index]) + " ";
		returnString += "\n";

		for (std::size_t index = 0; index < number.digits[1].size(); index++)
			returnString += std::to_string(number.digits[1][index]) + " ";

		return returnString;	
	}

private:
	std::array<std::vector<T>, 2> digits{};
	bool isNegative = false;

	static constexpr int countDigits()
	{
		int r = 0;
		T x = -1;
		while (x > 9)
		{
			x /= 10;
			r++;
		}
		return r;
	}

	void stringParser(const std::string& value, std::size_t destination, std::size_t start, std::size_t end)
	{
		T groupSum = 0;
		int count = 0;

		for (std::size_t index = end; index-- > start; count++)
		{
			if (std::isdigit(value[index]))
				groupSum += (T)(((value[index] - '0') * std::pow(10, count)));
			else
				throw std::invalid_argument("value can only contain numbers,  a single decimal point and +/- at the beginning");

			if (count == countDigits() - 1)
			{
				digits[destination].push_back(groupSum);
				groupSum = 0;
				count = -1;
			}
		}

		if (groupSum > 0)
			digits[destination].push_back(groupSum);
	}

public:
	Number(const char* value) : Number(std::string{ value }) {}

	Number(const std::string& value)
	{
		std::size_t offsetStart = (value[0] == '+' || ((value[0] == '-') ? (isNegative = true, true) : false));
		std::size_t offsetEnd = value.size();

		while (value[offsetStart] == '0')
			offsetStart++;

		while (value[offsetEnd - 1] == '0')
			offsetEnd--;

		std::size_t decimalIndex = value.find('.');

		if (decimalIndex == std::string::npos)
			decimalIndex = value.size();

		if (offsetStart <= decimalIndex && decimalIndex <= offsetEnd)
		{
			stringParser(value, 0, (std::size_t)offsetStart, decimalIndex);
			stringParser(value, 1, decimalIndex + 1, offsetEnd);
		}
		else
			throw std::invalid_argument("value can only contain numbers,  a single decimal point and +/- at the beginning");
	}

	template<typename V> requires std::is_arithmetic_v<V> Number(V value) : Number(std::to_string(value)){}

	Number operator+(const Number& addend)
	{

	}
};
