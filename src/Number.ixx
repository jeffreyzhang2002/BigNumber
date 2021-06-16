module;
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <tuple>
export module Number;

export class Number {
	friend std::string to_string(const Number& number);
	friend std::string to_string_raw(const Number& number);
	friend std::ostream& operator<<(std::ostream& os, const Number& number);

protected:
	std::vector<std::string> digits;
	std::vector<bool> isNegative;
	int radix;

	void stringParser(const std::string& value, unsigned int destination, unsigned int start, unsigned int end)
	{
		char sum = 0;
		bool next = false;

		for (int index = (int)(end - 1); index >= (int)start; index--)
		{
			if (std::isdigit(value[index]))
				sum += (value[index] - '0') * (next ? 10 : 1);
			else
				throw - 1;

			if (next)
			{
				digits[destination] += sum;
				sum = 0;
			}
			next = !next;
		}

		if (sum > 0)
			digits[destination] += sum;
	}

	Number(unsigned int numberFormat, const Number& other)
	{
		for (unsigned int index = 0; index < numberFormat; index++)
		{
			digits[index] = other.digits[index];
			if (index % 2 == 0)
				isNegative[index / 2] = other.isNegative[index / 2];
		}
	}

public:
	Number(unsigned int numberFormat) : digits(numberFormat, std::string{ "" }), isNegative((numberFormat - 1)/2 + 1, false), radix(10) {}

	Number(const Number& otherNumber)
	{
		digits = otherNumber.digits;
		isNegative = otherNumber.isNegative;
		radix = otherNumber.radix;
	}

private:
	std::tuple<std::string, unsigned char> addSegment(const std::string& addendA, const std::string& addendB)
	{
		std::string largerString, smallerString, output;

		addendA.size() < addendB.size() ? (smallerString = addendA, largerString = addendB) : (smallerString = addendB, largerString = addendA);

		unsigned char carry = 0;
		for (std::size_t index = 0; index < largerString.size(); index++)
		{
			unsigned char sum = (index < smallerString.size()? (unsigned char) smallerString[index] : 0) + (unsigned char)largerString[index] + (carry > 0? (unsigned char)carry-- : 0);
			if (sum >= 100)
			{
				carry += sum / 100;
				output += sum % 100;
			}
			else
				output += sum;
		}
		return std::make_tuple(output, carry);
	}

	std::tuple<std::string, bool, unsigned char> subtractSegment(const std::string& subtractendA, const std::string& subtractendB)
	{
		std::string largerString, smallerString, output;
		bool isNegative = subtractendB.size() > subtractendA.size();

		if (subtractendA.size() == subtractendB.size())
		{
			int index = subtractendA.size() - 1;
			while (index >= 0 && subtractendA[index] == subtractendB[index])
				index--;

			if (index >= 0)
			{
				subtractendA[index] < subtractendB[index] ? (smallerString = subtractendA, largerString = subtractendB, isNegative = true)
					: (smallerString = subtractendB, largerString = subtractendA, isNegative = false);
			}
			else
				return std::make_tuple(std::string{ 0 }, false, 0);
		}
		else
			subtractendA.size() < subtractendB.size() ? (smallerString = subtractendA, largerString = subtractendB) : (smallerString = subtractendB, largerString = subtractendA);

		signed char carry = 0;
		std::size_t index = 0;
		for (; index < smallerString.size(); index++)
		{
			int s = largerString[index] - (carry > 0? carry-- : 0);
		
			if (s < smallerString[index])
			{
				carry++;
				s += 100; //should add the radix * 10
			}

			output += (unsigned char) s - smallerString[index];
		}

		for (; index < largerString.size(); index++)
			output += largerString[index] - (carry > 0 ? carry-- : 0);
		

		return std::make_tuple(output, isNegative, carry);
	}
};

export std::string to_string_raw(const Number& number)
{
	std::string returnString{ "" };

	for (std::size_t i = 0; i < number.digits.size(); i++)
	{
		for (std::size_t j = 0; j < number.digits[i].size(); j++)
			returnString += std::to_string(number.digits[i][j]) + " ";
		returnString += "\n";
	}
	
	return returnString;
}

export std::string to_string(const Number& number)
{
	std::string returnString{""};

	for (std::size_t i = 0, j = 0; i < number.digits.size(); i++)
	{
		std::string section{ "" };
		for (int k = (int) number.digits[i].size() - 1; k >= 0; k--)
			section += std::to_string(number.digits[i][k]);
			
		if (i % 2 == 0)
			returnString += ((number.isNegative[j++]) ? "-" : "+") + section;
		else
			returnString += "." + section;
	}
	return returnString;
}

export std::ostream& operator<<(std::ostream& os, const Number& number)
{
	os << to_string(number);
	return os;
}