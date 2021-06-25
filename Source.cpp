#include <iostream>

import BigNumber;

int main()
{
	Number n = { 99.1234 };
	std::cout << to_string_raw(n) << "\n";

	Number b = { 9.876578 };
	std::cout << to_string_raw(b) << "\n";

	n + b;

}