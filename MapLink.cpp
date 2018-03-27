#include "stdafx.h"
#include "MapLink.h"

bool s2b(std::string s)
{
	if (s == "Open") return true;
	if (s == "Closed") return false;
	return false;
}