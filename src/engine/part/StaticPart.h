#pragma once
#include "Part.h"

class StaticPart :public Part
{
public:

	StaticPart() = default;
	//StaticPart(std::vector<PartPlugin> pps);

	//StaticPart addSubpart(int connectionPoint, Part* addedPart);

	//void makeHtml(std::ostream& html, InlineParts inlineParts) override;

	//std::vector<Part*> getAllParts() override;
	uint32_t getUniqueIdentifier() override;
	Fragment* getFragment(int index) override;
	//bool makeFragment(std::ostream& outStream, int index) override;
	//template<typename T>
	//T* at(int index);
protected:

	std::vector<Fragment> fragmentList;
	//std::map<int, Part*> containingParts;

	uint16_t partId = 0;
};

/*
template <typename T>
T* StaticPart::at(int index)
{
	try
	{
		return reinterpret_cast<T>(containingParts.at(index));
	}
	catch (std::exception e)
	{
		return nullptr;
	}
}
*/