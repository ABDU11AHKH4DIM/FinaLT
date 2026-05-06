#include "Command.h"

AddTransactionCommand::AddTransactionCommand(Budget* b, Transaction* t) : receiver(b), transaction(t) {}

AddTransactionCommand::~AddTransactionCommand()		// this class conditionally owns Transaction
{
	if (!inBudget)				// if the transation is NOT in Budget, only then delete it
		delete transaction;
}

void AddTransactionCommand::execute()			// override tells the compiler that this method is defining a virtual method of a parent class, and that its not a new method. so if no matching method is found, an error will be thrown
{
    receiver->pushTransaction(transaction);
    std::cout << "\n---> TRANSACTION ADDED <---\n";
    inBudget = true;
}

void AddTransactionCommand::undo()
{
    receiver->removeTransaction(transaction);
	inBudget = false;
}

DeleteTransactionCommand::DeleteTransactionCommand(Budget* b, Transaction* t) : receiver(b), transaction(t) {}

DeleteTransactionCommand::~DeleteTransactionCommand()		// this class conditionally owns Transaction
{
	if (!inBudget)				// if the transation is NOT in Budget, only then delete it. Temporary ownership. Transfer of ownership
		delete transaction;
}

void DeleteTransactionCommand::execute() 		// remove it from the Budget
{
	receiver->removeTransaction(transaction);
	std::cout << "\n---> TRANSACTION DELETED <---\n";
	inBudget = false;
}

void DeleteTransactionCommand::undo()			// add it back to Budget
{
	receiver->pushTransaction(transaction);
	inBudget = true;
}
