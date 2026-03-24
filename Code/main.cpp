#include <iostream>
#include "BudgetManager.h"
#include "Command.h"

int main()
{
	std::cout << "\n-------- FinaLT --------\n";
	
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
		
		std::cout << "\n==== CHOOSE AN OPTION ====\n"
				  << "1. Add a new transaction \t 2. Delete a transaction \t 3. List all transactions\n"
				  << "4. Switch Budget \t 5. Switch Category\n"
				  << "6. Add a new Budget \t 7. Add a new Category\n"
				  << "U. Undo \t R. Redo\n"
				  << "0. EXIT PROGRAM\n";
				  
		std::cin >> choice;
		
		switch (choice)
        {
            case '0':
                menuFlag = false;
                break;
            
            case '1':  // add transaction
            {
                if (currentCategory == nullptr)
                {
                    std::cout << "\nNo category selected! Use option 5 to select one.";
                    break;
                }
                Transactions* t = currentCategory->inputTransaction();
                Command* cmd = new AddTransactionCommand(currentCategory, t);
                manager.executeCommand(cmd);
            }
            break;
            
            case '2':  // delete transaction
            {
                if (currentCategory == nullptr)
                {
                    std::cout << "\nNo category selected! Use option 5 to select one.";
                    break;
                }
                currentCategory->listTransactions();
                
                std::string name;
                std::cout << "\nEnter transaction name: ";
                std::cin >> name;
                
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
                    std::cout << "\nNo category selected! Use option 5 to select one.";
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
                    std::cout << "\nNo budget selected! Use option 4 to select one.";
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
                std::cin >> budName;
                manager.addBudget(budName);
            }
            break;
            
            case '7':  // create category
            {
                if (currentBudget == nullptr)
                {
                    std::cout << "\nNo budget selected! Use option 4 to select one.";
                    break;
                }
                std::string catName;
                std::cout << "\nEnter category name: ";
                std::cin >> catName;
                currentBudget->addCategory(catName);
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
                std::cout << "\nInvalid input!";
        }
	}
	
	
//	while (menuFlag)
//	{
//		// editing may or may not be implemented. lets see what time says...
//		std::cout << "\n1. Create a New Transaction \t 2. Create a New Category \t 3.  Create a New Budget \t 4. List All Transactions \t 7. Delete a Transaction \t 'U'. Undo \t 'R'. Redo \t 0. Exit the Application\n";
//		std::cin >> choice; // needs input validation: If the user enters more than one character then throw an errorr
//		
//		switch (choice)
//		{
//			case '0': // inverted commas beacause choice is char
//				menuFlag = false;
//				break;
//				
//			case '1':
//			{
//				std::string budName;
//				std::cout << "\nEnter budget: ";
//				std::cin >> budName;
//				
//				Budget* b = manager.findBudget(budName);
//				if (b != nullptr)
//				{
//					std::string catName;
//			
//					std::cout << "\nEnter category: ";
//					std::cin >> catName;
//				
//					Category* c = b->findCategory(catName);
//					
//					if (c != nullptr)
//					{
//						Transactions* t = c->inputTransaction();
//						
//						Command* cmd = new AddTransactionCommand(c, t);		// this cmd is deleted in undo() inside BudgetManager
//						manager.executeCommand(cmd);						// adding the transaction to transactionVctr and pushing it onto undoStack
//					}						
//				
//					else
//						std::cout << "\nCategory not found!";
//				}
//					
//				else
//					std::cout << "\nBudget not found!";
//			}
//			break;
//				
//			case '2':
//			{
//				std::string budName;
//				std::cout << "\nEnter budget: " << std::endl;
//				std::cin >> budName;
//				
//				Budget* b = manager.findBudget(budName);
//				if (b != nullptr)
//				{
//					std::string catName;
//			
//					std::cout << "\nEnter category: " << std::endl;
//					std::cin >> catName;
//				
//					Category* c = b->findCategory(catName);
//					
//					if (c == nullptr)
//						b->addCategory(catName);
//					
//					else
//						std::cout << "\nCategory already exists!";						
//				}
//					
//				else
//					std::cout << "\nBudget not found!";
//			}
//			break;
//			
//			case '3':
//			{
//				std::string budName;
//				std::cout << "\nEnter budget: " << std::endl;
//				std::cin >> budName;
//				
//				Budget* b = manager.findBudget(budName);
//				
//				if (b == nullptr)
//					manager.addBudget(budName);
//					
//				else if (b != nullptr)
//					std::cout << "\nBudget already exists!";
//			}
//			break;
//			
//			case '4':
//			{
//				std::string budName;
//				std::cout << "\nEnter budget: " << std::endl;
//				std::cin >> budName;
//				
//				Budget* b = manager.findBudget(budName);
//				if (b != nullptr)
//				{
//					std::string catName;
//			
//					std::cout << "\nEnter category: " << std::endl;
//					std::cin >> catName;
//				
//					Category* c = b->findCategory(catName);
//					
//					if (c != nullptr)
//						c->listTransactions();
//					
//					else
//						std::cout << "\nCategory does not exist!";						
//				}
//					
//				else
//					std::cout << "\nBudget does not exist!";
//			}
//			break;
//			
//			case '7':
//			{
//				std::string budName;
//				std::cout << "\nEnter budget: " << std::endl;
//				std::cin >> budName;
//				
//				Budget* b = manager.findBudget(budName);
//				if (b != nullptr)
//				{
//					std::string catName;
//			
//					std::cout << "\nEnter category: " << std::endl;
//					std::cin >> catName;
//				
//					Category* c = b->findCategory(catName);
//					
//					if (c != nullptr)
//					{
//						c->listTransactions();
//						
//						std::string name;
//						std::cout << "\nEnter transaction name: ";
//						std::cin >> name;
//						
//						Transactions* t = c->findTransaction(name);
//						
//						if (t != nullptr)
//						{
//							Command* cmd = new DeleteTransactionCommand(c, t);
//							manager.executeCommand(cmd);
//						}
//						
//						else
//							std::cout << "\nTransaction does not exist!\n";
//					}
//					
//					else
//						std::cout << "\nCategory does not exist!";						
//				}
//					
//				else
//					std::cout << "\nBudget does not exist!";
//			}
//			break;
//			
//			case 'U':
//			case 'u':
//				manager.undo();
//				break;
//			
//			case 'R':
//			case 'r':
//				manager.redo();
//				break;
//			
//			default:
//				std::cout << "\nINVALID INPUT!";
//		}
//	}
}
