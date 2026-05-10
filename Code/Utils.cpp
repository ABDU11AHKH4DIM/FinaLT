#include "utils.h"

std::string tolowerString(std::string str)
{
	for (auto& x : str)
	{
		x = tolower(x);
	}
	
	return str;
}
std::string toupperString(std::string str)
{
	for (auto& y : str)
	{
		y = toupper(x);
	}
	
	return str;
}

