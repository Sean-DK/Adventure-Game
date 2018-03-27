//Sean Gaffney
//smgaffney@neo.rr.com

#include "stdafx.h"
#include "StringSplit.h"

std::vector<std::string> stringsplit(const std::string& s, const std::string& delim) {
	std::vector<std::string> result; //create a vector to be returned
	std::string str = s; //create a modifiable copy of the string
	do {
		if (delim == "" || str == "") return result; //if the string or delimiter are empty, return an empty vector
		else if (str.find(delim) == 0) str.erase(str.begin()); //if there is a delimiter at the beginning of the string, remove it
		else if (str.find(delim) > 0 && str.find(delim) < 32767) { //if there is a delimiter in the string
			result.push_back(str.substr(0, str.find(delim))); //add substring to the vector
			str.erase(str.begin(), str.begin() + str.find(delim) + delim.size()); //erase the substring from the string
		}
		else { //if there is no delimiter in the string
			result.push_back(str); //add the entire string to the vector
			return result; //return vector
		}
	} while (1);
}