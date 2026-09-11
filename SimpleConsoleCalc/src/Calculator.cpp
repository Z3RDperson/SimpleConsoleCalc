#include <iostream>
#include <string>
#include <vector>
#include "Calculator.h"

// Vector for operands
std::vector<Operand> operands; 

// Parse text into numbers and operators
double parser(std::string cleanPrompt)
{
	int last_op_index = 0; // Last operator seen in prompt

	/*
	 Loop through each character of prompt to extract numbers to be operated on
		 If you see an operator:
			 If last operator index was 0 (no operators seen):
				 All previous characters SINCE BEGINNING are a number
				 Save this number and the operator after it
			 Else all previous characters since last operator are a number
				 Save this number and the operator after it
			 Save the index of the operator in last_op_index
		 If you reached the end of prompt:
			 Save last number since last operator index (its operator: L "for last")


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


	 RETURN THE RESULT OF THE FINAL VECTOR ELEMENT
	*/
}

std::string cleaner(std::string prompt)
{
	std::string cleanPrompt;

	// Remove spaces and any characters other than integers and operators

	return cleanPrompt;
}