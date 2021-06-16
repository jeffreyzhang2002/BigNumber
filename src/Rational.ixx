module;

#include <string>
#include <iostream>

import Number;

export module Rational;

template<typename T>
concept FloatingPointType = std::is_floating_point<T>::value;

export class Rational : public Number {
public:
	Rational(const char* value) : Rational(std::string{ value }) {}

	Rational(const std::string& value) : Number(2)
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

		std::size_t last = value.size();
		while (value[last - 1] == '0')
			last--;
			
		std::size_t index = value.find('.');

		Number::stringParser(value, 0, offsetFront, index);
		Number::stringParser(value, 1, index + 1, last);
	}

	Rational(FloatingPointType auto value) : Rational(std::to_string(value)) { }

	Rational() : Rational(0.0) {}

	Rational(const Number& value) : Number(2, value) {}
};
