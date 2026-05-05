#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#include <vector>
#include <deque>
#include "Budget.h"
#include "Command.h"
#include "Utils.h"

/* the singleton
excerpt from Refactoring Guru:
All implementations of the Singleton have these two steps in common:

    1. Make the default constructor private, to prevent other objects from using the new operator with the Singleton class.
    2. Create a static creation method that acts as a constructor. Under the hood, this method calls the private constructor to create an object and saves it in a static field. All following calls to this method return the cached object.

If your code has access to the Singleton class, then it's able to call the Singleton's static method. So whenever that method is called, the same object is always returned. */

class BudgetManager  // INVOKER for command pattern
{
	private:
		BudgetManager();										// private constructor to prevent initialization in main()
		std::vector <Budget*> budgetVctr;						// vector to store pointers to 'Budget' objects
		std::deque <Command*> history;
		const int MAX_UNDO	= 10;
		int cursor = -1;										// this is the index of the last executed command. default value of -1 means that nothing can be undone, ie; end of history. if a command is executed, the index becomes 0 (counting starts from 0  :) in CS)
		
		BudgetManager(const BudgetManager&) = delete;			// deleting copy constructor
		BudgetManager& operator=(const BudgetManager&) = delete; // deleting assignment operator
		
	public:
		~BudgetManager();
		
		void ListBudgets();
		static BudgetManager& getInstance();					// a static method to call for
		Budget* takeInput();
				
		Budget* findBudget(std::string budName);
		void addBudget(std::string name);
		void executeCommand(Command* cmd);
		void undo();
		void redo();
};

#endif
