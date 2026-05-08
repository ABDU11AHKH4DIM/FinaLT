#pragma once
#include <string>			// for std::string
#include <ctime>			// for time_t

class Transaction
{
	private:
		double amount;
		std::string name;
		std::time_t timeInSeconds;
		
	public:
		Transaction(std::string name, double amount);
		Transaction(std::string name, double amount, std::time_t time);		// overloading constructors
		double getAmount();
		std::string getName();
		std::time_t getTimeInSeconds();
		char* getTimestamp();
};
