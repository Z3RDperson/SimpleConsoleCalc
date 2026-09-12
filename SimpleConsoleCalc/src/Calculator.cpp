#include <iostream>
#include <string>
#include <vector>
#include "Calculator.h"

// Global vector for operands
std::vector<Operand> operands; 

// Parse text into numbers and operators
long double parser(std::string cleanPrompt)
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
	
	printElements(); // FOR DEBUGGING PURPOSES

	// Do multiplication - division - modulo operations
	while (hasOperations_high())
	{
		for (int i = 0; i < operands.size(); i++)
		{
			switch (operands[i].getOpAfter())
			{
			case '*':
				solve_overwrite(i, multiply_w_next);
				break;

			case '/':
				solve_overwrite(i, divide_w_next);
				break;

			case '%':
				solve_overwrite(i, modulo_w_next);
				break;

			default:
				continue;
			}

			printElements(); // FOR DEBUGGING PURPOSES
			break;
		}
	}

	// Do Addition - Substraction operations
	while (hasOperations_low())
	{
		for (int i = 0; i < operands.size(); i++)
		{
			switch (operands[i].getOpAfter())
			{
			case '+':
				solve_overwrite(i, add_w_next);
				break;

			case '-':
				solve_overwrite(i, substract_w_next);
				break;
			}

			printElements(); // FOR DEBUGGING PURPOSES
			break;
		}
	}

	// RETURN THE RESULT OF THE FINAL VECTOR ELEMENT
	return operands[0].getNumber();
}

// Clean the prompt and add 'L' at end for last operand
std::string cleaner(std::string prompt)
{
	std::string cleanPrompt;

	// Remove spaces and any characters other than integers and operators

	// Add 'L' at the end so we know where the prompt stops
	cleanPrompt = prompt + "L";

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
	Operand operand;
	operand.setNumber(std::stod(numberBuffer));
	operand.setOpAfter(prompt[finishIndex]); // finish character is the operator after number

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

//===============================================================================

long double multiply_w_next(int index)
{
	return operands[index].getNumber() * operands[index + 1].getNumber();
}

long double divide_w_next(int index)
{
	return operands[index].getNumber() / operands[index + 1].getNumber();
}

long double modulo_w_next(int index)
{
	return (int)(operands[index].getNumber()) % (int) (operands[index + 1].getNumber());
}

bool hasOperations_high()
{
	for (Operand operand : operands)
	{
		if (operand.getOpAfter() == '*' || operand.getOpAfter() == '/' || operand.getOpAfter() == '%')
			return true;
	}

	return false;
}

long double add_w_next(int index)
{
	return operands[index].getNumber() + operands[index + 1].getNumber();
}

long double substract_w_next(int index)
{
	return operands[index].getNumber() - operands[index + 1].getNumber();
}

bool hasOperations_low()
{
	for (Operand operand : operands)
	{
		if (operand.getOpAfter() == '+' || operand.getOpAfter() == '-')
			return true;
	}

	return false;
}

void solve_overwrite(int index, long double (*operationPtr)(int))
{
	operands[index].setNumber(operationPtr(index));
	operands[index].setOpAfter(operands[index + 1].getOpAfter());
	operands.erase(operands.begin() + index + 1);
}



// FOR DEBUGGING ONLY : print vector contents
void printElements()
{
	for (Operand number : operands)
	{
		std::cout << number.getNumber() << " " << number.getOpAfter() << "\n";
	}

	std::cout << "------------------------------\n";
}