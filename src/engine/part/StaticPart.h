#pragma once
#include "Part.h"

class StaticPart:public Part
{
public:

	StaticPart() = default;
	//StaticPart(std::vector<PartPlugin> pps);
	
	StaticPart addSubpart(int connectionPoint, Part* addedPart);

	void makeHtml(std::ostream& html) override;

	std::vector<Part*> getAllParts() override;
	uint32_t getUniqueIdentifier() override;
protected:

	std::vector<Token> tokenList;
	std::map<int, Part*> containingParts;

	uint16_t partId;
};