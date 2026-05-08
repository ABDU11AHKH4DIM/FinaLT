#include "Transaction.h"
#include <ctime>

Transaction::Transaction(std::string name, double amount) : amount(amount), name(name)
{
	timeInSeconds = std::time(nullptr);
}

Transaction::Transaction(std::string name, double amount, std::time_t time) : name(name), amount(amount), timeInSeconds(time) {}

double Transaction::getAmount()
{
	return amount;
}

std::string Transaction::getName()
{
	return name;
}

std::time_t Transaction::getTimeInSeconds()
{
	return timeInSeconds;
}

char* Transaction::getTimestamp()
{
	return ctime(&timeInSeconds);
}