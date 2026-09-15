#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include "Calculator.h"

// Global vector for operands
std::vector<Operand> operands; 

// Parse text into numbers and operators
void parser(std::string cleanPrompt)
{
	int numberStart_index{ -1 }; // Character before first digit in the operand

	// Loop through each character of prompt
	// to extract numbers to be operated on
	for (int i = 0, length = (int) strlen(cleanPrompt.c_str()); i < length; i++)
	{
		if (isOperator(cleanPrompt[i]))
		{
			extract_store(cleanPrompt, numberStart_index, i);

			numberStart_index = i; // Re-assign to the character before next operand
		}
	}
	
	printElements(); // FOR DEBUGGING PURPOSES	
}

// Calculate user prompt
long double calculate()
{
	// Do multiplication - division - modulo operations
	while (hasOperations_high()) // if it still has operations of high order
	{
		for (int i = 0; i < operands.size(); i++)
		{
			// Determine operator and overwrite result to first operand
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
	while (hasOperations_low()) // if it still has operations of high order
	{
		for (int i = 0; i < operands.size(); i++)
		{
			// Determine operator and overwrite result to first operand
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
	for (int i = 0, length = (int) strlen(prompt.c_str()); i < length; i++)
	{
		if (std::isdigit(prompt[i]) || isOperator(prompt[i]))
		{
			cleanPrompt += prompt[i];
		}
	}

	// Add 'L' at the end so we know where the prompt stops
	cleanPrompt += "L";

	return cleanPrompt;
}

// Extract a number in a specified range of prompt text 
// and store it in operands vector
static void extract_store(std::string prompt, int startIndex, int finishIndex)
{
	std::string numberBuffer;

	for (int i = startIndex + 1; i < finishIndex; i++)
	{
		numberBuffer += prompt[i];
	}

	// Instantiate Operand object
	Operand operand(std::stod(numberBuffer), prompt[finishIndex]);
	// finish character is the operator after number

	// Store the operand in the vector
	operands.push_back(operand);
}

// Check if a character is an operator
static bool isOperator(char op)
{
	if (op == '+' || op == '-' 
		|| op == '*' || op == '/' || op == '%' || op == 'L')
		return true;
	else
		return false;
}

//=======================================================================

static long double multiply_w_next(int index)
{
	return operands[index].getNumber() * operands[index + 1].getNumber();
}

static long double divide_w_next(int index)
{
	return operands[index].getNumber() / operands[index + 1].getNumber();
}

static long double modulo_w_next(int index)
{
	return (int)(operands[index].getNumber()) 
		% (int) (operands[index + 1].getNumber());
}

static bool hasOperations_high()
{
	for (Operand operand : operands)
	{
		if (operand.getOpAfter() == '*' || operand.getOpAfter() == '/' 
			|| operand.getOpAfter() == '%')
			return true;
	}

	return false;
}

static long double add_w_next(int index)
{
	return operands[index].getNumber() + operands[index + 1].getNumber();
}

static long double substract_w_next(int index)
{
	return operands[index].getNumber() - operands[index + 1].getNumber();
}

static bool hasOperations_low()
{
	for (Operand operand : operands)
	{
		if (operand.getOpAfter() == '+' || operand.getOpAfter() == '-')
			return true;
	}

	return false;
}

static void solve_overwrite(int index, long double (*operationPtr)(int))
{
	operands[index].setNumber(operationPtr(index));
	operands[index].setOpAfter(operands[index + 1].getOpAfter());
	operands.erase(operands.begin() + index + 1);
}



// FOR DEBUGGING ONLY : print vector contents
static void printElements()
{
	for (Operand number : operands)
	{
		std::cout << number.getNumber() << " " << number.getOpAfter() << "\n";
	}

	std::cout << "------------------------------\n";
}