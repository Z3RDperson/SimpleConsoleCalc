// To use this calculator on a text prompt provided by user, follow these steps:
// 
// 1) Make sure user input contains numbers using : containDigits()
// 2) Clean text to produce a prompt of numbers & operators only using : cleaner()
// 3) Parse text into numbers and operators ...
//    to store them in operand array using : parser()
// 4) Calculate the final result from operands stored in the array using : calculate()

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
	for (int current_index = 0, length = cleanPrompt.size(); 
		current_index < length; current_index++)
	{
		if (isOperator(cleanPrompt[current_index]))
		{
			extract_store(cleanPrompt, numberStart_index, current_index);

			// Re-assign start index to the character before next operand (current)
			numberStart_index = current_index;
		}
	}
	
	printElements(); // FOR DEBUGGING PURPOSES	
}

// Calculate user prompt
long double calculate()
{
	// Do multiplication - division - modulo operations in operands vector
	// Operation functions argument is passed in solve_overwrite()
	while (hasOperations_high())
	{
		for (int i = 0, length = operands.size(); i < length; i++)
		{
			char op = operands[i].getOpAfter();

			switch (op)
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
				// Pass and move on if operator of low order
				continue;
			}

			printElements(); // FOR DEBUGGING PURPOSES
			break;
		}
	}

	// Do Addition - Substraction operations in operands vector
	// Operation functions arguments are passed in solve_overwrite()
	while (hasOperations_low())
	{
		for (int i = 0, length = operands.size(); i < length; i++)
		{
			char op = operands[i].getOpAfter();

			switch (op)
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

	// RETURN THE RESULT OF THE REMAINING VECTOR ELEMENT (1st element)
	return operands[0].getNumber();
}

// Clean the prompt and add 'L' at end for last operand
std::string cleaner(std::string prompt)
{
	std::string cleanPrompt;

	// Remove spaces and any characters other than integers, floating point 
	// and operators
	for (int i = 0, length = prompt.size(); i < length; i++)
	{
		if (std::isdigit(prompt[i]) || isOperator(prompt[i]) || prompt[i] == '.')
			cleanPrompt += prompt[i];
	}

	// Add 'L' at the end so we know Last operand
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
	// and initialize it with the number and operator after it
	Operand operand(std::stod(numberBuffer), prompt[finishIndex]);
	// NOTE: finish character is the operator after number

	// Store the operand in the global vector
	operands.push_back(operand);
}

// Check if a character is an operator
static bool isOperator(char op)
{
	return (op == '+' || op == '-' 
		|| op == '*' || op == '/' || op == '%' || op == 'L');
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

// Check if prompt still has operations of low order
static bool hasOperations_high()
{
	for (Operand operand : operands)
	{
		char op = operand.getOpAfter();

		if (op == '*' || op == '/' || op == '%')
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

// Check if prompt still has operations of low order
static bool hasOperations_low()
{
	for (Operand operand : operands)
	{
		char op = operand.getOpAfter();

		if (op == '+' || op == '-')
			return true;
	}

	return false;
}

// Solve operand on an index with one after it and overwrite the first
static void solve_overwrite(int index, long double (*operationPtr)(int))
{
	// Solve and overwrite selected operand (current "index") value & operator after:
	operands[index].setNumber(operationPtr(index));
	operands[index].setOpAfter(operands[index + 1].getOpAfter());

	// Remove the second operand
	operands.erase(operands.begin() + index + 1);
}



// Check if user raw text contains digits
bool containDigits(std::string user_text)
{
	for (int i = 0, length = user_text.size(); i < length; i++)
	{
		if (std::isdigit(user_text[i]))
		{
			return true;
		}
	}

	return false;
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