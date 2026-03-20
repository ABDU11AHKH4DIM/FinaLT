#include "Command.h"

// AddTransactionCommand
AddTransactionCommand::AddTransactionCommand(Category* cat, Transactions* t) : receiver(cat), transaction(t) {}

AddTransactionCommand::~AddTransactionCommand()
{
	delete transaction;
}

void AddTransactionCommand::execute()
{
    receiver->pushTransaction(transaction);
}

void AddTransactionCommand::undo()
{
    receiver->removeTransaction(transaction);
}

// DeleteTransactionCommand
DeleteTransactionCommand::DeleteTransactionCommand(Category* c, Transactions* t) : receiver(c), transaction(t) {}

DeleteTransactionCommand::~DeleteTransactionCommand()
{
	delete transaction;
}

void DeleteTransactionCommand::execute()
{
	receiver->removeTransaction(transaction);
}

void DeleteTransactionCommand::undo()
{
	receiver->pushTransaction(transaction);
}
