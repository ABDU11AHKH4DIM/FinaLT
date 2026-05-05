#include "Command.h"

// AddTransactionCommand
AddTransactionCommand::AddTransactionCommand(Category* cat, Transactions* t) : receiver(cat), transaction(t) {}

AddTransactionCommand::~AddTransactionCommand()
{
	if (!inCategory)
		delete transaction;
}

void AddTransactionCommand::execute()
{
    receiver->pushTransaction(transaction);
    inCategory = true;
}

void AddTransactionCommand::undo()
{
    receiver->removeTransaction(transaction);
    inCategory = false;
}

// DeleteTransactionCommand
DeleteTransactionCommand::DeleteTransactionCommand(Category* c, Transactions* t) : receiver(c), transaction(t) {}

DeleteTransactionCommand::~DeleteTransactionCommand()
{
	if (!inCategory)
		delete transaction;
}

void DeleteTransactionCommand::execute()
{
	receiver->removeTransaction(transaction);
	inCategory = false;
}

void DeleteTransactionCommand::undo()
{
	receiver->pushTransaction(transaction);
	inCategory = true;
}
