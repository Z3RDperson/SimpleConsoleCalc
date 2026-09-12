#include <iostream>
#include <string>
#include <vector>
#include "Calculator.h"

// Vector for pointers to operands
std::vector<Operand*> operands; 

// Parse text into numbers and operators
double parser(std::string cleanPrompt)
{
	int numberStart_index{ -1 };

	// Loop through each character of prompt to extract numbers to be operated on
	for (int i = 0, length = (int) strlen(cleanPrompt.c_str()); i < length; i++)
	{
		if (isOperator(cleanPrompt[i]))
		{
			extract_store(cleanPrompt, numberStart_index, i);

			numberStart_index = i;
		}
	}

	// RETURN THE RESULT OF THE FINAL VECTOR ELEMENT
	return 1;

	/*
	While there is still multiplication/division/modulo left:
		Loop through each number in operands vector/array
			If operator after is multiplication or division or modulo:
				Solve the operand with the one after it
				Store result in first one (overwrite its value)
				Store the operator after the second operand in first one
				Erase second operand from the vector

	While there is still addition/substraction left:
		Loop through each number in operands vector/array
			If operator after is addition/substraction:
				Solve the operand with the one after it
				Store result in first one (overwrite its value)
				Store the operator after the second operand in first one
				Erase second operand from the vector
	*/
}

// Clean the prompt and add 'L' at end for last operand
std::string cleaner(std::string prompt)
{
	std::string cleanPrompt;

	// Remove spaces and any characters other than integers and operators

	// Add 'L' at the end so we know where the prompt stops

	return cleanPrompt;
}

// Extract a number in a specified range of prompt text and store it in operands vector
void extract_store(std::string prompt, int startIndex, int finishIndex)
{
	std::string numberBuffer;

	for (int i = startIndex + 1; i < finishIndex; i++)
	{
		numberBuffer += prompt[i];
	}

	// Instantiate Operand object
	Operand* operand = new Operand;
	operand->setNumber(std::stod(numberBuffer));
	operand->setOpAfter(prompt[finishIndex]); // finish character is the operator after number

	// Store the operand in the vector
	operands.push_back(operand);
}

// Check if a character is an operator
bool isOperator(char op)
{
	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '%' || op == 'L')
		return true;
	else
		return false;
}

// FOR DEBUGGING ONLY : print vector contents
void printElements()
{
	for (Operand* number : operands)
	{
		std::cout << number->getNumber() << " " << number->getOpAfter()
			<< "\n";
	}
}