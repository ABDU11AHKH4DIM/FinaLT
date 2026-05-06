#include "Budget.h"
#include "utils.h"

Budget::Budget(std::string name, double limit) : name(name), limit(limit) {}

Budget::~Budget()
{
	for (Transaction* t : transactionVctr)
		delete t;
}

std::string Budget::getName()
{
	return name;
}

void Budget::setName(std::string name)
{
	this -> name = name;
}

double Budget::getLimit()
{
	return limit;
}

void Budget::setLimit(double limit)
{
	this -> limit = limit;
}

double Budget::getTotalSpent()						// on the fly calculations help reduce the code because the changes are automatically done
{
	double total = 0;
	for (Transaction* t : transactionVctr)
		total += t->getAmount();
		
	return total;
}

double Budget::getRemaining()
{
	return limit - getTotalSpent();
}

void Budget::listTransaction()
{
	if (transactionVctr.empty())
		std::cout << "\nNo transactions found!\n";
	
	else
	{
		for (auto* x : transactionVctr)
		{
		std::cout << "\n" << x->getName() << "\t|\t" << x->getAmount() << "\t|\t" << x->getTimeOfCreation();
		}
	}
}

void Budget::pushTransaction(Transaction* t)
{
	transactionVctr.push_back(t);
}

Transaction* Budget::inputTransaction()
{
	std::string name, details;
	std::cout << "\nEnter transaction name: ";
	std::getline(std::cin, name);
	
	double amount;
	std::cout << "\nEnter amount: ";
	std::cin >> amount;
	while (std::cin.fail())
	{
		std::cin.clear();		// resets the fail 'alarms'
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			// ignores or 'discards' all the characters before and including the newline character
		
		std::cout << "\nINVALID INPUT!\n";
		std::cin >> amount;
	}
	
	Transaction* t = new Transaction(name, amount);
	
	return t;
}

Transaction* Budget::findTransaction(std::string name)  // to search if a transaction already exists
{
	for (Transaction* t : transactionVctr)
	{
		if (tolowerString(name) == tolowerString(t->getName()))
			return t;
	}
	
	return nullptr;		// i.e; not found
}

void Budget::removeTransaction(Transaction* t)  // this method is required for undo as it does NOT delete the object itself
{
	auto it = std::find(transactionVctr.begin(), transactionVctr.end(), t);			// .begin() returns the first element of the vector
	if (it != transactionVctr.end())												// .end() returns an imaginary element after the last element of the vector, not the last element itself.
		transactionVctr.erase(it);
}
