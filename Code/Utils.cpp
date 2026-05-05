#include "utils.h"

std::string tolowerString(std::string str)
{
	for (auto& x : str)
	{
		x = tolower(x);
	}
	
	return str;
}
