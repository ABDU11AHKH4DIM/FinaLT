#include "Category.h"
#include <iostream>

Category::Category(std::string name) : name(name){}

Category::~Category()
{
	for (Transactions* t : transactionVctr)
        delete t;
}

std::string Category::getName()
{
	return name;
}

void Category::listTransactions()
{
	for (auto x : transactionVctr)
	{
		std::cout << "\n" << x->getName();
	}
}

void Category::pushTransaction(Transactions* t)
{
	transactionVctr.push_back(t);
}

Transactions* Category::inputTransaction()
{
	std::string name, details;
	double amount;
	
	std::cout << "\nEnter the name" << std::endl;
	std::cin >> name; 
	
	std::cout << "\nEnter amount: " << std::endl;
	std::cin >> amount;
	
	std::cout << "\nEnter details: " << std::endl;
	std::cin >> details;
	
	Transactions* t = new Transactions(name, amount, details); // DO NOT FORGET TO USE DELETE
	
	return t;
}

Transactions* Category::findTransaction(std::string name)  // to search if a transaction already exists
{
	for (Transactions* t : transactionVctr)
	{
		if (tolowerString(name) == tolowerString(t->getName()))
			return t;
	}
	
	return nullptr; // not found, i.e; create new category
}

void Category::removeTransaction(Transactions* t) // this method is required for undo because it does NOT delete the object itself
{
	transactionVctr.erase(std::remove(transactionVctr.begin(), transactionVctr.end(), t), transactionVctr.end());  // erase-remove idiom. std::remove shifts (removes) all the occurrences of 't' to the end, and .erase deletes them from the vector. std::remove itself only makes the value unspecified state, it does not deallocate memory
}
