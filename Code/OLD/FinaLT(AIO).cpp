#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <deque>
	
	//FUNCTIONS
	std::string tolowerString(std::string str)
	{
		for (auto& x : str)
		{
			x = tolower(x);
		}
		
		return str;
	}
	
	// CLASSES
	class Transactions
	{
		private:
			double amount;
			// date and time
			std::string name;
			std::string details;
			
		public:
			Transactions(std::string name, double amount, std::string details/*, date and time*/) : amount(amount), name(name), details(details) {}
			
			double getAmount()
			{
				return amount;
			}
			
			std::string getName()
			{
				return name;
			}
			
			std::string getDetails()
			{
				return details;
			}
	};
	
	class Category  // RECEIVER
	{
		private:
			std::string name;
			std::vector <Transactions*> transactionVctr;  // a vector to store pointers to 'Transactions' objects
		
		public:
			Category(std::string name) : name(name){}
			
			std::string getName()
			{
				return name;
			}
			
			void listTransactions()
			{
				for (auto x : transactionVctr)
				{
					std::cout << "\n" << x->getName() << "\n";
				}
			}
			
			void pushTransaction(Transactions* t)
			{
				transactionVctr.push_back(t);
			}
						
			Transactions* inputTransaction()
			{
				std::string name, details;
				double amount;
				
				std::cout << "\nEnter the name" << std::endl;
				std::cin >> name; 
				
				std::cout << "\nEnter amount: " << std::endl;
				std::cin >> amount;
				
				std::cout << "\nEnter details: " << std::endl;
				std::cin >> details;
				
				Transactions* t = new Transactions(name, amount, details); // DO NOT FORGET TO USE DELETE
				
				return t;
			}
			
			Transactions* findTransaction(std::string name)  // to search if a transaction already exists
			{
				for (Transactions* t : transactionVctr)
				{
					if (tolowerString(name) == tolowerString(t->getName()))
						return t;
				}
				
				return nullptr; // not found, i.e; create new category
			}
			
			void removeTransaction(Transactions* t) // this method is required for undo because it does NOT delete the object itself
			{
				transactionVctr.erase(std::remove(transactionVctr.begin(), transactionVctr.end(), t), transactionVctr.end());  // erase-remove idiom. std::remove shifts (removes) all the occurrences of 't' to the end, and .erase deletes them from the vector. std::remove itself only makes the value unspecified state, it does not deallocate memory
			}
};
	
	class Budget // for multiple budgets
	{
		private:
			std::string name;
			double limit;
	//		double daily;  // a daily spending limit calculated using limit and budget duration, exceeding this will cause it  to be recalculated
	//		int duration;  // to-do
			std::vector <Category*> categoryVctr; // a vector to store pointers to 'Category' objects
			
		public:
			Budget(std::string name, double limit) : name(name), limit(limit) {}
			~Budget()
			{
				for (Category* c : categoryVctr)
				{
					delete c;
				}
			}
			
			std::string getName()
			{
				return name;
			}
			
			Category* findCategory(std::string catName)  // to search if a category already exists
			{
				for (Category* c : categoryVctr)
				{
					if (tolowerString(catName) == tolowerString(c->getName()))
						return c;
				}
				
				return nullptr; // not found, i.e; create new category
			}
			
			void addCategory(std::string catName)
			{	
				if (findCategory(catName) == nullptr)	
					categoryVctr.push_back(new Category(catName));
				
				else
					std::cout << "\nCategory already exists!";
			}
	};
	
class Command  // base command
{
	public:
		virtual void execute()	= 0;
		virtual void undo()		= 0;
		
		virtual ~Command() {};
};

class AddTransactionCommand : public Command    // concrete command
{
    private:
        Category* receiver;      // the object that does the actual work
        Transactions* transaction; // the data needed to do and undo
    
    public:
        AddTransactionCommand(Category* cat, Transactions* t) : receiver(cat), transaction(t) {}
        ~AddTransactionCommand()
        {
        	delete transaction;
		}
        
        void execute() override
        {
            receiver->pushTransaction(transaction);
        }
        
        void undo() override  // override tells the compiler that this method is defining a virtual method of a parent class, and that its not a new method. so if no matching method is found, an error will be thrown
        {
            receiver->removeTransaction(transaction);
        }
};
class DeleteTransactionCommand : public Command
{
	private:
		Category* receiver;
		Transactions* transaction;
		
	public:
		DeleteTransactionCommand(Category* c, Transactions* t) : receiver(c), transaction(t) {}
		~DeleteTransactionCommand()
		{
			delete transaction;		
		}
		
		void execute() override
		{
			receiver->removeTransaction(transaction);
		}
		
		void undo() override
		{
			receiver->pushTransaction(transaction);
		}
		
};
	
	/* the singleton
	excerpt from Refactoring Guru:
	All implementations of the Singleton have these two steps in common:
	
	    1. Make the default constructor private, to prevent other objects from using the new operator with the Singleton class.
	    2. Create a static creation method that acts as a constructor. Under the hood, this method calls the private constructor to create an object and saves it in a static field. All following calls to this method return the cached object.
	
	If your code has access to the Singleton class, then it’s able to call the Singleton’s static method. So whenever that method is called, the same object is always returned. */
	
	class BudgetManager  // INVOKER for command pattern
	{
		private:
			BudgetManager() { std::cout << "Called\n";}		// private constructor to prevent initialization in main()
			std::vector <Budget*> budgetVctr;				// vector to store pointers to 'Budget' objects
			std::deque <Command*> history;
			const int MAX_UNDO	= 10;
			int cursor = -1;								// this is the index of the last executed command. default value of -1 means that nothing can be undone, ie; end of history
			
			BudgetManager(const BudgetManager&) = delete;	// deleting copy constructor
			BudgetManager& operator=(const BudgetManager&) = delete; // deleting assignment operator
			
		public:
			~BudgetManager()
			{
				for (Budget* b : budgetVctr) 
					delete b;
				
				for (Command* cmd : history) 
					delete cmd;
			}
			static BudgetManager& getInstance()  // a static mathod to call for
			{
				static BudgetManager instance;  // static ensures that its created only once along with the private constructor
				return instance;
			}
			
			Budget* findBudget(std::string budName)
			{
				for (Budget* b : budgetVctr)
				{
					if (tolowerString(budName) == tolowerString(b->getName()))
						return b;
				}
				
				return nullptr;
			}
			
			void addBudget(std::string name)
			{
				if (findBudget(name) == nullptr)
				{
					double limit;
					std::cout << "\nEnter budget limit: ";
					std::cin >> limit;
					
					budgetVctr.push_back(new Budget(name, limit));
				}
				
				else
					std::cout << "\nBudget already exists!";  // i may need to remove this if-else checking because its not this methods job
			}
			
			void executeCommand(Command* cmd)
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
			
			void undo()
			{
				if (cursor < 0)
				{
					std::cout << "\nNothing to undo!";
					return;
				}
				
				history[cursor] -> undo();
				cursor--;
			}
			
			void redo()
			{
				if (cursor + 1 >= (int)history.size())
				{
					std::cout << "\nNothing to redo!";
					return;
				}
				
				cursor++; 						// move the cursor right, ie; _undo_ the undo()
				history[cursor] -> execute();	// then execute that command
			}
	};
	
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
