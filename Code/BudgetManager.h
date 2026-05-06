#pragma once
#include <deque>			// for std::deque
#include <iostream>			// for input/output
#include <limits>			// for std::numeric_limits and max()
#include <string>			// for std::string
#include "Command.h"

// ============================================================
// BudgetManager  (INVOKER for command pattern — Singleton)
// ============================================================

class BudgetManager  // INVOKER for command pattern
{
	private:
		BudgetManager();									// private constructor to prevent initialization in main()
		Budget* currentBudget = nullptr;					// only *one* budget exists
		std::deque <Command*> history;						// Deque stands for 'Double-ended queue'. Chose a deque because of pop_front() and push_front()
		const int MAX_UNDO	= 10;							// max undo/redo limit of 10
		int cursor = -1;									// this is the index of the last executed command. default value of -1 means that nothing can be undone, ie; end of history. 
															// if a command is executed, the index becomes. counting starts from 0  :)
		
		BudgetManager(const BudgetManager&) = delete;				// deleting copy constructor
		BudgetManager& operator=(const BudgetManager&) = delete;	// deleting assignment operator
		
	public:
		~BudgetManager(); 									// BudgetManager owns Budget
		static BudgetManager& getInstance();  				// a static mathod to call for
		Budget* getBudget();
		void createNewBudget();
		void editBudget();

// 		COMMANDS
		
		void executeCommand(Command* cmd);
		void undo();
		void redo();
};
