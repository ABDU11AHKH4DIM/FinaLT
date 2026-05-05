#include "Transaction.h"

Transaction::Transaction(std::string name, double amount) : amount(amount), name(name){}

double Transaction::getAmount()
{
	return amount;
}

std::string Transaction::getName()
{
	return name;
}
