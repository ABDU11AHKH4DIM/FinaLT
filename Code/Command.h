#pragma once
#include "Budget.h"

// ============================================================
// Command  (base + concrete commands)
// ============================================================

class Command  // BASE/ABSTRACT COMMAND
{
	public:
		virtual void execute()	= 0;
		virtual void undo()		= 0;
		
		virtual ~Command() {};
};

class AddTransactionCommand : public Command    // CONCRETE COMMAND
{
    private:
        Budget* receiver;      			// the object that does the actual work
        Transaction* transaction; 		// the data needed to do and undo
        bool inBudget = false;			// Transfer of ownership. Need this flag for memory management, because in some case Transaction pointers become dangling pointers. 
										// default is false beacause when this command is created the pointer is NOT in the budgetVctr vector
    
    public:
        AddTransactionCommand(Budget* b, Transaction* t);
        ~AddTransactionCommand();		// this class conditionally owns Transaction
        void execute() override;		// override tells the compiler that this method is defining a virtual method of a parent class, and that its not a new method. so if no matching method is found, an error will be thrown
        void undo() override;
};

class DeleteTransactionCommand : public Command
{
	private:
		Budget* receiver;
		Transaction* transaction;
		bool inBudget = true;			// Transfer of ownership. Need this flag for memory management, because in some case Transaction pointers become dangling pointers. 
										// default is true beacause when this command is created the pointer is already in the category vector
		
	public:
		DeleteTransactionCommand(Budget* b, Transaction* t);
		~DeleteTransactionCommand();	// this class conditionally owns Transaction
		void execute() override; 		// remove it from the Budget
		void undo() override;			// add it back to Budget
};
