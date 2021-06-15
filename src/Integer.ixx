module;

#include <string>
#include <type_traits>
#include <iostream>

import Number;

export module Integer;

template<typename T>
concept IntegralType = std::is_integral<T>::value;

export class Integer : public Number {
public:
	Integer(const char* value) : Integer(std::string{ value }) {}

	Integer(const std::string& value) : Number(1) 
	{
		bool offsetFront = false;
		if (value[0] == '-') 
		{
			isNegative[0] = true;
			offsetFront = true;
		}
		else if (value[0] == '+')
		{
			isNegative[0] = false;
			offsetFront = true;
		}

		Number::stringParser(value, 0, (unsigned int) offsetFront, value.size());
	}

	Integer(IntegralType auto value) : Number(1)
	{
		if (value < 0)
		{
			isNegative[0] = value < 0;
			value *= -1;
		}
		while (value > 0)
		{
			digits[0] += value % 100;
			value /= 100;
		}
	}

	Integer() : Integer(0) {};


};