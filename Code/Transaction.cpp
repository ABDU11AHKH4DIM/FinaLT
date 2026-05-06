#include "Transaction.h"
#include <ctime>

Transaction::Transaction(std::string name, double amount) : amount(amount), name(name)
{
	timeOfCreation = std::time(nullptr);
}

double Transaction::getAmount()
{
	return amount;
}

std::string Transaction::getName()
{
	return name;
}

char* Transaction::getTimeOfCreation()
{
	return ctime(&timeOfCreation);					// ctime() return an array of characters
}