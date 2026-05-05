#pragma once
#include <string>			// for std::string

// ============================================================
// Transaction
// ============================================================

class Transaction
{
	private:
		double amount;
		std::string name;
		
	public:
		Transaction(std::string name, double amount);
		double getAmount();
		std::string getName();
};
