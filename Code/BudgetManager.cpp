#include "BudgetManager.h"
#include <sstream>

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

void BudgetManager::saveData()
{
	std::ofstream saveData{"UserData.csv"};
	
	if (!saveData)
	{
		std::cout << "\n!!! ERROR: COULD NOT SAVE !!!\n";
		return;
	}
	
	saveData << currentBudget->getName() << "," << currentBudget->getLimit() << "\n";		// first row is always the budget
		
	saveData << "label,amount,timestamp\n";			// second row is the column names for the transactions
	
	for (auto* i : currentBudget->getTransactionVctr())
	{
		saveData << i->getName() << "," << i->getAmount() << "," << i->getTimeInSeconds() << "\n";
	}
	
	saveData.close();
}

void BudgetManager::loadData()
{
	std::ifstream saveData{"UserData.csv"};
	
	if (!saveData)
	{
		std::cout << "\n!!! ERROR: COULD NOT LOAD TRANSACTIONS !!!\n";
		return;
	}
		
	std::string line;						// each line in the csv file
	
	if (std::getline(saveData, line))
	{
		std::stringstream ss(line);
		
		std::string budgetName, budgetLimitStr;
		
		std::getline(ss, budgetName, ',');
		std::getline(ss, budgetLimitStr);
		
		currentBudget = new Budget(budgetName, std::stod(budgetLimitStr));
	}
	
	std::getline(saveData, line);			// skipping the first line because it has the names of each column. the program will crash when trying to convert amountStr to double.
	
	while (std::getline(saveData, line))
	{
		std::stringstream ss(line);			// turning the string into an input stream
		std::string nameStr, amountStr, timeStr;
		
		std::getline(ss, nameStr, ',');			// comman is the delimiter. getline() will read the nameStr string variable until it reaches a comma. (the comma is what separates each column in the csv file)
		std::getline(ss, amountStr, ',');		// same as above
		std::getline(ss, timeStr);				// no delimiter because time is the last column
		
		currentBudget->pushTransaction(new Transaction(nameStr, std::stod(amountStr), std::stoll(timeStr)));			// stod = string to double. converting the amountStr to a double
																														// stoll = string to long long. converting the timeStr to a long long. (std::time_t is usually a long long int)
	}
	
	saveData.close();
}

void BudgetManager::createNewBudget()
{
	std::string budName;
	std::cout << "\nEnter budget name: ";
	std::getline(std::cin, budName);

	std::string bud_Currency = currentBudget -> ValidCurrency();
	
	double limit;
	std::cout << "\nEnter budget limit: ";
	std::cin >> limit;
	
	while (std::cin.fail())					// Input validation
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cout << "\n!!! INVALID INPUT !!!\n";
		std::cin >> limit;
	}
	
	for (Command* cmd : history) delete cmd;
	history.clear();
	cursor = -1;
	delete currentBudget;
	
	currentBudget = new Budget(budName, limit, bud_Currency);
}

void BudgetManager::editBudget()
{
	std::cout << "\n=== Edit name ===\n";
    std::string name;
    std::cout << "\nEnter name: ";
    std::getline(std::cin, name);
    currentBudget->setName(name);

	std::cout << "\n=== Edit Currency ===\n";
    std::string validcurr = Budget::ValidCurrency();
	currentBudget->setCurrency(validcurr);
    
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
    
    std::cout << "\n---> BUDGET EDITED SUCCESSFULLY <---\n";
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
		std::cout << "\n!!! NOTHING TO UNDO !!!\n";
		return;
	}
	
	history[cursor] -> undo();
	cursor--;
	std::cout << "\n---> UNDO PERFORMED <---\n";
}

void BudgetManager::redo()
{
	if (cursor + 1 >= (int)history.size())
	{
		std::cout << "\n!!! NOTHING TO REDO !!!\n";
		return;									// no need for an else block because of this early return
	}
	
	cursor++; 									// move the cursor right (increment), ie; _undo_ the undo()
	history[cursor] -> execute();				// then execute that command
	std::cout << "\n---> REDO PERFORMED <---\n";
}
