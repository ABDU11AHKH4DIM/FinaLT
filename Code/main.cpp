#include <iostream>
#include "BudgetManager.h"
#include "Command.h"

int main()
{
	std::cout << "\n======== FinaLT ========\n";
	
	BudgetManager& manager = BudgetManager::getInstance();  // used a reference because it points to the same instance. Without it, the copy constructor will be invoked, which has been deleted for this class
	
	// main menu
	Budget* currentBudget = nullptr;  // these current objects help simpilfy the menu and create a better UX
	Category* currentCategory = nullptr;
	
	char choice;
	bool menuFlag = true; // used a flag so that the prgram can be terminated from inside a switch case
	
	while (menuFlag)
	{
		std::cout << "\nCurrently in Budget: " << (currentBudget != nullptr ? currentBudget->getName() : "NULL" )
				  << "\t|\t"
				  << "Currently in Category: " << (currentCategory != nullptr ? currentCategory->getName() : "NULL" )
				  << "\n";
		
		std::cout << "\n---- CHOOSE AN OPTION ----\n"
				  << "1. Add a new transaction \t 2. Delete a transaction \t 3. List all transactions\n"
				  << "4. Switch Budget \t 5. Switch Category\n"
				  << "6. Add a new Budget \t 7. Add a new Category\n"
				  << "U. Undo \t R. Redo\n"
				  << "0. EXIT PROGRAM\n";
		
		std::cin >> choice;
		discardInput();			// input validation
		
		switch (choice)
        {
            case '0':
                menuFlag = false;
                break;
            
            case '1':  // add transaction
            {
                if (currentCategory == nullptr)
                {
                    std::cout << "\nNo category selected! Use option 5 to select one.\n";
                    break;
                }
                Transactions* t = currentCategory->inputTransaction();
                Command* cmd = new AddTransactionCommand(currentCategory, t);	// this cmd is deleted in undo() inside BudgetManager
                manager.executeCommand(cmd);									// adding the transaction to transactionVctr and pushing it onto undoStack
            }
            break;
            
            case '2':  // delete transaction
            {
                if (currentCategory == nullptr)
                {
                    std::cout << "\nNo category selected! Use option 5 to select one.\n";
                    break;
                }
                currentCategory->listTransactions();
                
                std::string name;
                std::cout << "\nEnter transaction name: ";
                std::getline(std::cin, name);
                
                Transactions* t = currentCategory->findTransaction(name);
                if (t != nullptr)
                {
                    Command* cmd = new DeleteTransactionCommand(currentCategory, t);
                    manager.executeCommand(cmd);
                }
                else
                    std::cout << "\nTransaction not found!";
            }
            break;
            
            case '3':  // list transactions
            {
                if (currentCategory == nullptr)
                {
                    std::cout << "\nNo category selected! Use option 5 to select one.\n";
                    break;
                }
                currentCategory->listTransactions();
            }
            break;
            
            case '4':  // switch budget
            {
                Budget* b = manager.takeInput();
                if (b != nullptr)
                {
                    currentBudget = b;
                    currentCategory = nullptr;  // reset category when budget changes
                    std::cout << "\nSwitched to budget: " << currentBudget->getName();
                }
            }
            break;
            
            case '5':  // switch category
            {
                if (currentBudget == nullptr)
                {
                    std::cout << "\nNo budget selected! Use option 4 to select one.\n";
                    break;
                }
                Category* c = currentBudget->takeInput();
                if (c != nullptr)
                {
                    currentCategory = c;
                    std::cout << "\nSwitched to category: " << currentCategory->getName();
                }
            }
            break;
            
            case '6':  // create budget
            {
                std::string budName;
                std::cout << "\nEnter budget name: ";
                std::getline(std::cin, budName);
                
                manager.addBudget(budName);  // addBudget handles the amount
            }
            break;
            
            case '7':  // create category
            {
                if (currentBudget == nullptr)
                {
                    std::cout << "\nNo budget selected! Use option 4 to select one.\n";
                    break;
                }
                std::string catName;
                std::cout << "\nEnter category name: ";
                std::getline(std::cin, catName);
                
                currentBudget->addCategory(catName);
            }
            break;
            
            case 'u':
            case 'U':
                manager.undo();
                std::cout << "\n*UNDO PERFORMED*\n";
                break;
            
            case 'r':
            case 'R':
                manager.redo();
                std::cout << "\n*REDO PERFORMED*\n";
                break;
            
            default:
                std::cout << "\nINVALID INPUT\n";
        }
	}
}