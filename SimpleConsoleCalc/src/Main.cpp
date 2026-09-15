#include <iostream>
#include <string>
#include "Calculator.h"

int main()
{
	// Get user input
	std::cout << "Type a prompt: ";
	std::string buffer;
	std::getline(std::cin, buffer);

	// Clean and parse text
	std::string cleanPrompt = cleaner(buffer);
	parser(cleanPrompt);

	// Calculate user prompt
	long double result = calculate();

	// Print result
	std::cout << "Result       : " << result << std::endl;

	std::cin.get();
}