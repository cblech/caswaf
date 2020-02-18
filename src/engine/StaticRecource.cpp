#include "StaticRecource.h"
#include <iostream>

std::vector<char> Resource::initializeResourceData(const fs::path& resoucePath)
{
	std::ifstream ifs(resoucePath.string(),std::ios::binary);

	if (ifs.is_open())
	{
		std::vector<char> retVal;

		char c = ifs.get();
		while (!ifs.eof())
		{
			retVal.push_back(c);
			c = ifs.get();
		}

		return retVal;

	}
	throw std::exception("resource not available.");
}
