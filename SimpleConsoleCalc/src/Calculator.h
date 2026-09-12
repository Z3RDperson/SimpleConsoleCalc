#pragma once

// Functions Declarations
double parser(std::string cleanPrompt);
std::string cleaner(std::string prompt);
void extract_store(std::string prompt, int startIndex, int finishIndex);
bool isOperator(char op);

// FOR DEBUGGING ONLY
void printElements();

// Operand class definition
class Operand
{
public:
	void setNumber(double user_number)
	{
		m_number = user_number;
	}

	void setOpAfter(char opAfter)
	{
		m_opAfter = opAfter;
	}

	double getNumber() const
	{
		return m_number;
	}

	char getOpAfter() const
	{
		return m_opAfter;
	}

private:
	double m_number;
	char m_opAfter;
};
