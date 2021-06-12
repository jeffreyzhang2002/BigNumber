module;
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
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

public:
	Number(unsigned int numberFormat) : digits(numberFormat, std::string{ "" }), isNegative((numberFormat - 1)/2 + 1, false), radix(10) {}

	Number(const Number& otherNumber)
	{
		digits = otherNumber.digits;
		isNegative = otherNumber.isNegative;
		radix = otherNumber.radix;
	}

	const std::vector<bool>& getNegatives() const
	{ return const_cast<std::vector<bool>&>(isNegative); }

	bool getNegative(std::size_t index) const
	{ return isNegative[index]; }

	const std::vector<std::string>& getDigitsRaw() const
	{ return const_cast<std::vector<std::string>&>(digits);}

	const std::string& getDigitsSectionRaw(std::size_t index) const
	{
		return const_cast<std::string&>(digits[index]);
	}

	const Number operator+(const Number& other) const
	{

	}

	const Number operator-(const Number& other) const
	{

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