#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>

class Transactions
{
	private:
		double amount;
		// date and time
		std::string name;
		std::string details;
		
	public:
		Transactions(std::string name, double amount, std::string details/*, date and time*/);
		
		double getAmount();
		std::string getName();
		std::string getDetails();
};

#endif
