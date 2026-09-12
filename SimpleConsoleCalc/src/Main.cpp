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
	//std::string cleanPrompt = cleaner(buffer);
	double result = parser(buffer);

	// Print result
	printElements();

	std::cin.get();
}