#pragma once
#include <string>			// for std::string
#include <ctime>			// for time_t

class Transaction
{
	private:
		double amount;
		std::string name;
		std::time_t timeOfCreation;
		
	public:
		Transaction(std::string name, double amount);
		double getAmount();
		std::string getName();
		char* getTimeOfCreation();
};
