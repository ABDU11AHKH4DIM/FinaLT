#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include <algorithm>
#include "Transactions.h"
#include "Utils.h"

class Category  // RECEIVER
{
	private:
		std::string name;
		std::vector <Transactions*> transactionVctr;	// a vector to store pointers to 'Transactions' objects
	
	public:
		Category(std::string name);
		~Category();
		
		std::string getName();
		void listTransactions();
		void pushTransaction(Transactions* t);
		Transactions* inputTransaction();
		Transactions* findTransaction(std::string name);
		void removeTransaction(Transactions* t);  // this method is required for undo because it does NOT delete the object itself
};

#endif
