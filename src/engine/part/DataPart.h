#pragma once
#include "Part.h"

class DataPart: public Part
{
public:
	//std::vector<Part*> getAllParts() override;
	uint32_t getUniqueIdentifier() override;

	//virtual Part* make() = 0;
};
