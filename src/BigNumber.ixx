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

	void stringParser(const std::string& value, std::size_t destination, std::size_t start, std::size_t end, bool reverse=false)
	{
		T groupSum = 0;

		if (reverse)
		{
			int count = countDigits() - 1;
			for (std::size_t index = start; index < end; index++,count--)
			{
				if (std::isdigit(value[index]))
					groupSum += (T)(((value[index] - '0') * std::pow(10, count)));
				else
					throw std::invalid_argument("value can only contain numbers,  a single decimal point and +/- at the beginning");

				if (count == 0)
				{
					digits[destination].push_back(groupSum);
					groupSum = 0;
					count = countDigits();
				}
			}
		}
		else
		{
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
		}

		if (groupSum > 0)
			digits[destination].push_back(groupSum);
	}

public:
	Number() { }
	
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
			stringParser(value, 1, decimalIndex + 1, offsetEnd, true);
		}
		else
			throw std::invalid_argument("value can only contain numbers,  a single decimal point and +/- at the beginning");
	}

	template<typename V> requires std::is_arithmetic_v<V> Number(V value) : Number(std::to_string(value)){}

	Number add(const Number<T>& addend) const {
		Number<T> sum{};
		T carry = 0;
		T maxDigitSize = (T)std::pow(10, countDigits());

		for (std::size_t group = 2; group-- > 0;)
		{
			std::size_t addendSize = addend.digits[group].size(), thisSize = digits[group].size(), length = std::max(addend.digits[group].size(), digits[group].size());
			sum.digits[group] = std::vector<T>(length, (T)0);

			for (std::size_t index = (group == 1) ? length : 0; (group == 1) ? index-- > 0: index < length; (group == 1) ? 0 : index++)
			{
				if (index < addendSize && index < thisSize)
				{
					T currentsum = digits[group][index] + addend.digits[group][index] + ((carry > 0) ? carry-- : 0);
					if (currentsum > maxDigitSize - 1)
					{
						carry += currentsum / maxDigitSize;
						currentsum %= maxDigitSize;
					}
					sum.digits[group][index] = currentsum;
				}
				else if (index < addendSize)
					sum.digits[group][index] = addend.digits[group][index];
				else
					sum.digits[group][index] = digits[group][index];
			}
		}
		if (carry > 0)
			sum.digits[0].push_back(carry);

		return sum;
	}

	Number operator+(const Number<T>& addend) const
	{ return add(addend); }
};
