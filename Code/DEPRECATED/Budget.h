#ifndef BUDGET_H
#define BUDGET_H

#include <string>
#include <vector>
#include "Category.h"
#include "Utils.h"

class Budget // for multiple budgets
{
	private:
		std::string name;
		double limit;
//		double daily;  // a daily spending limit calculated using limit and budget duration, exceeding this will cause it  to be recalculated
//		int duration;  // to-do
		std::vector <Category*> categoryVctr; // a vector to store pointers to 'Category' objects
		
	public:
		Budget(std::string name, double limit);
		~Budget();
		
		std::string getName();
		Category* takeInput();
		Category* findCategory(std::string catName);
		void addCategory(std::string catName);
};

#endif
