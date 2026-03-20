#include "Budget.h"
#include <iostream>

Budget::Budget(std::string name, double limit) : name(name), limit(limit) {}

Budget::~Budget()
{
	for (Category* c : categoryVctr)
	{
		delete c;
	}
}

std::string Budget::getName()
{
	return name;
}

Category* Budget::findCategory(std::string catName)  // to search if a category already exists
{
	for (Category* c : categoryVctr)
	{
		if (tolowerString(catName) == tolowerString(c->getName()))
			return c;
	}
	
	return nullptr; // not found, i.e; create new category
}

void Budget::addCategory(std::string catName)
{	
	if (findCategory(catName) == nullptr)	
		categoryVctr.push_back(new Category(catName));
	
	else
		std::cout << "\nCategory already exists!";
}
