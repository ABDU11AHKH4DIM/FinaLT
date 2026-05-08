#pragma once
#include <string>			// for std::string
#include <vector>			// for std::vector
#include <iostream>			// for input/output
#include <limits>			// for std::numeric_limits and max()
#include <algorithm>		// for std::remove()
#include "Transaction.h"

// ============================================================
// Budget  (RECEIVER)
// ============================================================

class Budget  // RECEIVER
{
	private:
		std::string name;
		double limit;
		std::vector <Transaction*> transactionVctr;	// a vector to store pointers to 'Transaction' objects
	
	public:
		Budget(std::string name, double limit);
		~Budget();
		
		std::string getName();
		
		void setName(std::string name);
		
		double getLimit();
		
		void setLimit(double limit);
		
		double getTotalSpent();						// on the fly calculations help reduce the code because the changes are automatically done
		
		double getRemaining();
		
		const std::vector<Transaction*>& getTransactionVctr();
		
		void listTransaction();
		
		void pushTransaction(Transaction* t);
		
		Transaction* inputTransaction();
		
		Transaction* findTransaction(std::string name);  // to search if a transaction already exists
		
		void removeTransaction(Transaction* t);  // this method is required for undo as it does NOT delete the object itself
};
