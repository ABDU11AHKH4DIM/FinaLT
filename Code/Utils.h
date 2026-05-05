#pragma once
#include <string>			// for std::string
#include <cctype>			// for tolower()

// commenting out cctype and limits headers won't give compile errors, but they are used in this program. This might be because of 'Transitive includes'.

// ============================================================
// Utils
// ============================================================

std::string tolowerString(std::string str);
