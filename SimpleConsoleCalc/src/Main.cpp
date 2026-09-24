#include <iostream>
#include <string>
#include "Calculator.h"

int main()
{
	for (; ;)
	{
		std::string buffer;

		// Get user input
		do
		{
			std::cout << "Type a prompt: ";
			std::getline(std::cin, buffer);
		} while (!containDigits(buffer));

		// Clean and parse text
		std::string cleanPrompt = cleaner(buffer);
		parser(cleanPrompt);

		// Calculate user prompt
		long double result = calculate();

		// Print result
		std::cout << "Result       : " << result << std::endl;

		std::cout << "==============================\n" << std::endl;
	}
}