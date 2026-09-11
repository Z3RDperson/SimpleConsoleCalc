#pragma once

// Functions Declarations

// Operand class definition
class Operand
{
public:
	void setNumber(double user_number)
	{
		m_number = user_number;
	}

	double getNumber() const
	{
		return m_number;
	}

private:
	double m_number;
	char m_opAfter;
};
