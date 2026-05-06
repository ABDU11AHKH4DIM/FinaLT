#include "BudgetManager.h"

BudgetManager::BudgetManager()	{}									// private constructor to prevent initialization in main()

BudgetManager::~BudgetManager() 									// BudgetManager owns Budget
{	
	delete currentBudget;							// even if currentBudget is nullptr, no problem. delete has built-in checks for that
	
	for (Command* cmd : history)					// BudgetManager owns Command
		delete cmd;									// deleting the history
}

BudgetManager& BudgetManager::getInstance()  				// a static mathod to call for
{
	static BudgetManager instance;  				// static ensures that its created only once along with the private constructor
	return instance;
}

Budget* BudgetManager::getBudget()
{
	return currentBudget;
}

void BudgetManager::createNewBudget()
{
	std::string budName;
	std::cout << "\nEnter budget name: ";
	std::getline(std::cin, budName);
	
	double limit;
	std::cout << "\nEnter budget limit: ";
	std::cin >> limit;
	
	while (std::cin.fail())					// Input validation
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cout << "\nINVALID INPUT!\n";
		std::cin >> limit;
	}
	
	for (Command* cmd : history) delete cmd;
	history.clear();
	cursor = -1;
	delete currentBudget;
	
	currentBudget = new Budget(budName, limit);
}

void BudgetManager::editBudget()
{
	std::cout << "\n=== Edit name ===\n";
    std::string name;
    std::cout << "\nEnter name: ";
    std::getline(std::cin, name);
    currentBudget->setName(name);
    
    std::cout << "\n=== Edit limit ===\n";
    double limit;
    std::cout << "\nEnter limit: ";
    std::cin >> limit;
    
    while (std::cin.fail())
    {
    	std::cin.clear();
    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    	std::cout << "\n!!! INVALID INPUT !!!\n\n"
    			  << "Enter limit: ";
    	std::cin >> limit;
	}
    currentBudget->setLimit(limit);
}

void BudgetManager::executeCommand(Command* cmd)
{
	while ((int)history.size() > cursor + 1)	// casting history.size() to int because it returns an unsigned int, as cursor is signed. 
	{
		delete history.back();					// deleting the history after the cursor because if a user performs a new action after undo then redo cannot be performed because it becomes invalid
		history.pop_back();
	}
	
	cmd->execute();								// execute the command
	history.push_back(cmd);						// add it to history deque
	cursor++;									// move the pointer forward (increment the index) to point at it
	
	if ((int)history.size() > MAX_UNDO) 		// if the history is too big
	{
		delete history.front();					// delete the oldest command pointer
		history.pop_front();					// remove from history
		cursor--;								// move the cursor back (decrement) to compensate
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
	std::cout << "\n*UNDO PERFORMED*\n";
}

void BudgetManager::redo()
{
	if (cursor + 1 >= (int)history.size())
	{
		std::cout << "\nNothing to redo!";
		return;									// no need for an else block because of this early return
	}
	
	cursor++; 									// move the cursor right (increment), ie; _undo_ the undo()
	history[cursor] -> execute();				// then execute that command
	std::cout << "\n*REDO PERFORMED*\n";
}
