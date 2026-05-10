#include <iostream>			// for input/output
#include <limits>			// for std::numeric_limits and max()
#include <iomanip>			// for formatting text
#include "BudgetManager.h"
#include <windows.h>		// for SetConsoleOutput()

// ============================================================
// main
// ============================================================

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	 std::cout << R"(

                        ███████╗██╗███╗   ██╗ █████╗ ██╗  ████████╗
                        ██╔════╝██║████╗  ██║██╔══██╗██║  ╚══██╔══╝
                        █████╗  ██║██╔██╗ ██║███████║██║     ██║   
                        ██╔══╝  ██║██║╚██╗██║██╔══██║██║     ██║   
                        ██║     ██║██║ ╚████║██║  ██║███████╗██║   
                        ╚═╝     ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚═╝   

                    )"; 
	
	BudgetManager& manager = BudgetManager::getInstance();  // used a reference because it points to the same instance. Without it, the copy constructor will be invoked, which has been deleted for this class
	
	manager.loadData();
	Budget* currentBudget = manager.getBudget();
	
	if (currentBudget == nullptr)
	{
		std::cout << "\nPlease, add a budget to start using this app.\n";       
        manager.createNewBudget();  					// addBudget handles the amount
        currentBudget = manager.getBudget();
	}
	
	// MAIN MENU
	char choice;
	bool menuFlag = true;									// used a flag so that the prgram can be terminated from inside a switch case
	
	while (menuFlag)
	{
		std::cout << std::left
				  << "\nBudget Name: " << std::setw(16) << (currentBudget != nullptr ? currentBudget->getName() : "NULL" )
				  << "| "
				  << "PKR " << std::setw(8) << currentBudget->getRemaining() << " left of PKR " << currentBudget->getLimit()
				  << " (PKR " << currentBudget->getTotalSpent() << " spent)\n";
		
		std::cout << "\n---- CHOOSE AN OPTION ----\n\n"
				  << "1. Add a new transaction \t 2. Delete a transaction \t 3. List all Transaction\n"
				  << "4. Edit Budget \t 5. Create a new budget\n"
				  << "U. Undo \t R. Redo\n"
				  << "0. EXIT PROGRAM\n";
		
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			// cleaning input buffer
		
		switch (choice)
        {
            case '0':
            	manager.saveData();
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
            	manager.editBudget();
            }
            break;
            
            case '5':
            {
            	manager.createNewBudget();
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
                std::cout << "\n!!! INVALID INPUT !!!\n";
        }
	}
}
