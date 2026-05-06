#include <iostream>			// for input/output
#include <limits>			// for std::numeric_limits and max()
#include "BudgetManager.h"

// ============================================================
// main
// ============================================================

int main()
{
	std::cout << "\n======== FinaLT ========\n";
	
	BudgetManager& manager = BudgetManager::getInstance();  // used a reference because it points to the same instance. Without it, the copy constructor will be invoked, which has been deleted for this class
	
	// MAIN MENU
	char choice;
	bool menuFlag = true;									// used a flag so that the prgram can be terminated from inside a switch case
	
	while (menuFlag)
	{
		Budget* currentBudget = manager.getBudget();
		
		if (currentBudget == nullptr)
		{
			std::cout << "\nPlease, add a budget to start using this app.\n";
                
            manager.createNewBudget();  					// addBudget handles the amount
            currentBudget = manager.getBudget();
		}
		
		std::cout << "\nBudget Name: " << (currentBudget != nullptr ? currentBudget->getName() : "NULL" )
				  << "\t|\t"
				  << "PKR " << currentBudget->getRemaining() << " left of PKR " << currentBudget->getLimit()
				  << "\t(PKR " << currentBudget->getTotalSpent() << " spent)\n";
		
		std::cout << "\n---- CHOOSE AN OPTION ----\n\n"
				  << "1. Add a new transaction \t 2. Delete a transaction \t 3. List all Transaction\n"
				  << "4. Edit Budget\n"
				  << "U. Undo \t R. Redo\n"
				  << "0. EXIT PROGRAM\n";
		
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			// cleaning input buffer
		
		switch (choice)
        {
            case '0':
                menuFlag = false;
                break;
            
            case '1':  // add transaction
            {
                Transaction* t = currentBudget->inputTransaction();
                Command* cmd = new AddTransactionCommand(currentBudget, t);		// this cmd is deleted in undo() inside BudgetManager
                manager.executeCommand(cmd);									// adding the transaction to transactionVctr and pushing it onto undoStack
            }
            break;
            
            case '2':  // delete transaction
            {
                currentBudget->listTransaction();
                
                std::string name;
                std::cout << "\nEnter transaction name: ";
                std::getline(std::cin, name);
                
                Transaction* t = currentBudget->findTransaction(name);
                if (t != nullptr)
                {
                    Command* cmd = new DeleteTransactionCommand(currentBudget, t);
                    manager.executeCommand(cmd);
                }
                else
                    std::cout << "\nTransaction not found!";
            }
            break;
            
            case '3':  // list Transaction
            {
                currentBudget->listTransaction();
            }
            break;
            
            case '4':  // edit budget
            {
                std::cout << "\n=== Edit name ===\n";
                std::string name;
                std::cout << "\nEnter name: ";
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			// called because of getline()
                std::getline(std::cin, name);
                currentBudget->setName(name);
                
                std::cout << "\n=== Edit limit ===\n";
                double limit;
                std::cout << "\nEnter limit: ";
                std::cin >> limit;
                currentBudget->setLimit(limit);
            }
            break;
            
            case 'u':
            case 'U':
                manager.undo();
                break;
            
            case 'r':
            case 'R':
                manager.redo();
                break;
            
            default:
                std::cout << "\nINVALID INPUT\n";
        }
	}
}
