#pragma once
#include <string>

class starstring :public std::string 
{
public:
	starstring() :std::string("") {}
	starstring(std::string s) :std::string(s) {}
	bool equals(std::string s)
	{
		int j = 0;
		for (int i = 0; i < s.length(); i++)
		{
			if (j >= length())
				return false;

			if (at(j) != '*')
			{
				if (s.at(i) != at(j))
					return false;

				j++;
			}
			else
			{
				if (j == length() - 1)
					return true;
				else if (i == s.length() - 1)
					return false;
				else if (s.at(i + 1) == at(j + 1))
					if (starstring(substr(j + 1)).equals(s.substr(i + 1)))
						return true;

			}
			
		}
		if (j < length())
			return false;

		return true;
	}
};


