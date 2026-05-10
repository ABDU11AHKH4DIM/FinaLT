#pragma once
#include <string>			// for std::string
#include <cctype>			// for tolower() and toupper()

// commenting out cctype and limits headers won't give compile errors, but they are used in this program. This might be because of 'Transitive includes'.

// ============================================================
// Utils
// ============================================================
std::string toupperString(std::string str);
std::string tolowerString(std::string str);
