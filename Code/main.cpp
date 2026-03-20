#include <iostream>
#include "BudgetManager.h"
#include "Command.h"

int main()
{
	std::cout << "\n-------- FinaLT --------\n";
	
	BudgetManager& manager = BudgetManager::getInstance();  // used a reference because it points to the same instance. Without it, the copy constructor will be invoked, which has been deleted for this class
	
	// main menu
	char choice;
	bool menuFlag = true; // used a flag so that the prgram can be terminated from inside a switch case
	
	while (menuFlag)
	{
		// editing may or may not be implemented. lets see what time says...
		std::cout << "\n1. Create a New Transaction \t 2. Create a New Category \t 3.  Create a New Budget \t 4. List All Transactions \t 7. Delete a Transaction \t 'U'. Undo \t 'R'. Redo \t 0. Exit the Application\n";
		std::cin >> choice; // needs input validation: If the user enters more than one character then throw an errorr
		
		switch (choice)
		{
			case '0': // inverted commas beacause choice is char
				menuFlag = false;
				break;
				
			case '1':
			{
				std::string budName;
				std::cout << "\nEnter budget: ";
				std::cin >> budName;
				
				Budget* b = manager.findBudget(budName);
				if (b != nullptr)
				{
					std::string catName;
			
					std::cout << "\nEnter category: ";
					std::cin >> catName;
				
					Category* c = b->findCategory(catName);
					
					if (c != nullptr)
					{
						Transactions* t = c->inputTransaction();
						
						Command* cmd = new AddTransactionCommand(c, t);		// this cmd is deleted in undo() inside BudgetManager
						manager.executeCommand(cmd);						// adding the transaction to transactionVctr and pushing it onto undoStack
					}						
				
					else
						std::cout << "\nCategory not found!";
				}
					
				else
					std::cout << "\nBudget not found!";
			}
			break;
				
			case '2':
			{
				std::string budName;
				std::cout << "\nEnter budget: " << std::endl;
				std::cin >> budName;
				
				Budget* b = manager.findBudget(budName);
				if (b != nullptr)
				{
					std::string catName;
			
					std::cout << "\nEnter category: " << std::endl;
					std::cin >> catName;
				
					Category* c = b->findCategory(catName);
					
					if (c == nullptr)
						b->addCategory(catName);
					
					else
						std::cout << "\nCategory already exists!";						
				}
					
				else
					std::cout << "\nBudget not found!";
			}
			break;
			
			case '3':
			{
				std::string budName;
				std::cout << "\nEnter budget: " << std::endl;
				std::cin >> budName;
				
				Budget* b = manager.findBudget(budName);
				
				if (b == nullptr)
					manager.addBudget(budName);
					
				else if (b != nullptr)
					std::cout << "\nBudget already exists!";
			}
			break;
			
			case '4':
			{
				std::string budName;
				std::cout << "\nEnter budget: " << std::endl;
				std::cin >> budName;
				
				Budget* b = manager.findBudget(budName);
				if (b != nullptr)
				{
					std::string catName;
			
					std::cout << "\nEnter category: " << std::endl;
					std::cin >> catName;
				
					Category* c = b->findCategory(catName);
					
					if (c != nullptr)
						c->listTransactions();
					
					else
						std::cout << "\nCategory does not exist!";						
				}
					
				else
					std::cout << "\nBudget does not exist!";
			}
			break;
			
			case '7':
			{
				std::string budName;
				std::cout << "\nEnter budget: " << std::endl;
				std::cin >> budName;
				
				Budget* b = manager.findBudget(budName);
				if (b != nullptr)
				{
					std::string catName;
			
					std::cout << "\nEnter category: " << std::endl;
					std::cin >> catName;
				
					Category* c = b->findCategory(catName);
					
					if (c != nullptr)
					{
						c->listTransactions();
						
						std::string name;
						std::cout << "\nEnter transaction name: ";
						std::cin >> name;
						
						Transactions* t = c->findTransaction(name);
						
						if (t != nullptr)
						{
							Command* cmd = new DeleteTransactionCommand(c, t);
							manager.executeCommand(cmd);
						}
						
						else
							std::cout << "\nTransaction does not exist!\n";
					}
					
					else
						std::cout << "\nCategory does not exist!";						
				}
					
				else
					std::cout << "\nBudget does not exist!";
			}
			break;
			
			case 'U':
			case 'u':
				manager.undo();
				break;
			
			case 'R':
			case 'r':
				manager.redo();
				break;
			
			default:
				std::cout << "\nINVALID INPUT!";
		}
	}
}
