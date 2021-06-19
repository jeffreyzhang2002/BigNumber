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

	void stringParser(const std::string& value, unsigned int destination, unsigned int start, unsigned int end, bool alignedLeft = true)
	{
		char sum = 0;
		bool next = false;

		if (alignedLeft)
		{
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
		else
		{
			for (int index = start; index < (int)end; index++)
			{
				if (std::isdigit(value[index]))
					sum += (value[index] - '0') * (next ? 1 : 10);
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
			std::reverse(digits[destination].begin(), digits[destination].end());
		}
		
	}

	Number(unsigned int numberFormat, const Number& other) : Number(numberFormat)
	{
		for (unsigned int index = 0; index < std::min(numberFormat, (unsigned int)other.digits.size()); index++)
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

	//Number operator+(const Number& addend) const
	//{
	//	unsigned int max = std::max(addend.digits.size(), digits.size());
	//	unsigned char carry = 0;

	//	Number sum{ max };

	//	for (unsigned int index = 0; index < max; index += 2)
	//	{
	//		if (index < addend.digits.size() && index < digits.size())
	//		{
	//			
	//		}
	//	}		
	//}

private:
	bool greaterThanSegment(const Number& comparedNumber, unsigned int index) const
	{
		if (digits[index].size() == comparedNumber.digits[index].size())
		{
			for (int i = 0; i < digits[index].size(); i++)
				if (digits[index][i] > comparedNumber.digits[index][i])
					return true;
			return false;
		}
		return digits[index].size() > comparedNumber.digits[index].size();
	}

	bool lessThanSegment(const Number& comparedNumber, unsigned int index) const
	{
		if (digits[index].size() == comparedNumber.digits[index].size())
		{
			for (int i = 0; i < digits[index].size(); i++)
				if (digits[index][i] < comparedNumber.digits[index][i])
					return true;
			return false;
		}
		return digits[index].size() < comparedNumber.digits[index].size();
	}

	bool equalToSegment(const Number& comparedNumber, unsigned int index) const
	{
		return (digits[index] != comparedNumber.digits[index]);
	}

	std::tuple<std::string, unsigned char> addSegment(const std::string& addendA, const std::string& addendB, unsigned char carry = 0) const
	{
		std::string largerString, smallerString, output;

		addendA.size() < addendB.size() ? (smallerString = addendA, largerString = addendB) : (smallerString = addendB, largerString = addendA);

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

	std::tuple<std::string, bool, unsigned char> subtractSegment(const std::string& subtractendA, const std::string& subtractendB) const
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

	void addSegmentHelper(const Number& addend, unsigned int index, Number& returnedNumber) const
	{
		if (addend.isNegative[index / 2] == isNegative[index / 2])
		{
			unsigned char carry = 0;

			if (index + 1 < addend.digits.size())
			{
				std::tuple<std::string, unsigned char> s1 = addSegment(addend.digits[index + 1], digits[index + 1], carry);
				returnedNumber.digits[index + 1] = std::get<0>(s1);
				carry = std::get<1>(s1);
			}
	
			std::tuple<std::string, unsigned char> s2 = addSegment(addend.digits[index], digits[index], carry);
			returnedNumber.digits[index] = (std::get<1>(s2) != 0) ? ((char)std::get<1>(s2) + std::get<0>(s2)) : std::get<0>(s2);
			returnedNumber.isNegative[index / 2] = addend.isNegative[index / 2];
		}
		else
		{
			// not sure yet
		}
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