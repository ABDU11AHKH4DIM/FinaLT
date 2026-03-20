#ifndef COMMAND_H
#define COMMAND_H

#include "Category.h"
#include "Transactions.h"

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
        AddTransactionCommand(Category* cat, Transactions* t);
        ~AddTransactionCommand();
        
        void execute() override;
        void undo() override;  // override tells the compiler that this method is defining a virtual method of a parent class, and that its not a new method. so if no matching method is found, an error will be thrown
};

class DeleteTransactionCommand : public Command
{
	private:
		Category* receiver;
		Transactions* transaction;
		
	public:
		DeleteTransactionCommand(Category* c, Transactions* t);
		~DeleteTransactionCommand();
		
		void execute() override;
		void undo() override;
};

#endif
