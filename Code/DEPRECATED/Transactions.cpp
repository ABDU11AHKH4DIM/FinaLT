#include "Transactions.h"

Transactions::Transactions(std::string name, double amount, std::string details/*, date and time*/) : amount(amount), name(name), details(details) {}

double Transactions::getAmount()
{
	return amount;
}

std::string Transactions::getName()
{
	return name;
}

std::string Transactions::getDetails()
{
	return details;
}
