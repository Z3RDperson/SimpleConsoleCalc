#include <iostream>
#include <string>

int main()
{
	std::cout << "Type the operation you need\n" 
		<< "(Multiplication - Division - Difference - Sum) : " << std::endl;

	// String buffer to take input from user
	std::string op = " ";
	std::getline(std::cin, op);

	std::cin.get();
	return 0;
}