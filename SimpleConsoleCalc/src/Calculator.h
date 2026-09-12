#pragma once

// Operand class definition
class Operand
{
public:
	void setNumber(long double user_number)
	{
		m_number = user_number;
	}

	void setOpAfter(char opAfter)
	{
		m_opAfter = opAfter;
	}

	long double getNumber() const
	{
		return m_number;
	}

	char getOpAfter() const
	{
		return m_opAfter;
	}

private:
	long double m_number;
	char m_opAfter;
};


long double parser(std::string cleanPrompt);
std::string cleaner(std::string prompt);
void extract_store(std::string prompt, int startIndex, int finishIndex);
bool isOperator(char op);

long double multiply_w_next(int index);
long double divide_w_next(int index);
long double modulo_w_next(int index);
bool hasOperations_high();
long double add_w_next(int index);
long double substract_w_next(int index);
bool hasOperations_low();

void solve_overwrite(int index, long double (*operationPtr)(int));

// FOR DEBUGGING ONLY
void printElements();
