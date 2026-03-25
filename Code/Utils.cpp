#include "Utils.h"
#include <iostream>
#include <cctype>
#include <limits>

std::string tolowerString(std::string str)
{
	for (auto& x : str)
	{
		x = tolower(x);
	}
	
	return str;
}

void discardInput()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void recoverInput()  // for in case std::cin enters  fail state
{
	if (std::cin.fail())
	{
		std::cin.clear();
		discardInput();
	}
}