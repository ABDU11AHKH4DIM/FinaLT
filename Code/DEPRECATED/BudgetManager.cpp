#include "BudgetManager.h"
#include <iostream>

BudgetManager::BudgetManager() {}

BudgetManager::~BudgetManager()
{
	for (Budget* b : budgetVctr) 
		delete b;
	
	for (Command* cmd : history) 
		delete cmd;
}

void BudgetManager::ListBudgets()
{
	for (Budget* b : budgetVctr)
		std::cout << "\n" << b->getName();
}

BudgetManager& BudgetManager::getInstance()  // a static mathod to call for
{
	static BudgetManager instance;  // static ensures that its created only once along with the private constructor
	return instance;
}

Budget* BudgetManager::takeInput()
{
	std::string budName;
	std::cout << "\nEnter budget: ";
	std::getline(std::cin, budName);
	
	Budget* b = findBudget(budName);
	
	if (b == nullptr)
		std::cout << "\nBUDGET NOT FOUND!\n";

	return b;  // b is returned regardless
}

Budget* BudgetManager::findBudget(std::string budName)
{
	for (Budget* b : budgetVctr)
	{
		if (tolowerString(budName) == tolowerString(b->getName()))
			return b;
	}
	
	return nullptr;
}

void BudgetManager::addBudget(std::string name)
{
	if (findBudget(name) == nullptr)
	{
		double limit;
		std::cout << "\nEnter budget limit: ";
		std::cin >> limit;
		while (std::cin.fail())
		{
			recoverInput();
			std::cout << "\nINVALID INPUT!\n";
			std::cin >> limit;
		}		
		budgetVctr.push_back(new Budget(name, limit));
	}
	
	else
		std::cout << "\nBudget already exists!";  // i may need to remove this if-else checking because its not this methods job
}

void BudgetManager::executeCommand(Command* cmd)
{
	while ((int)history.size() > cursor + 1)
	{
		delete history.back();
		history.pop_back();
	}
	
	cmd->execute();				// execute the command
	history.push_back(cmd);		// add it to history
	cursor++;					// move the pointer forward to point at it
	
	if ((int)history.size() > MAX_UNDO)  // if the history is too big
	{
		delete history.front();		// delete the oldest command pointer
		history.pop_front();		// remove from history
		cursor--;					// move the cursor back to compensate
	}
}

void BudgetManager::undo()
{
	if (cursor < 0)
	{
		std::cout << "\nNothing to undo!";
		return;
	}
	
	history[cursor] -> undo();
	cursor--;
}

void BudgetManager::redo()
{
	if (cursor + 1 >= (int)history.size())
	{
		std::cout << "\nNothing to redo!";
		return;
	}
	
	cursor++; 						// move the cursor right, ie; _undo_ the undo()
	history[cursor] -> execute();	// then execute that command
}
