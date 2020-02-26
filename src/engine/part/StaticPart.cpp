#include "StaticPart.h"


//StaticPart::StaticPart(std::vector<PartPlugin> pps)
//{
//}

StaticPart StaticPart::addSubpart(int connectionPoint, Part* addedPart)
{
	containingParts.try_emplace(connectionPoint, addedPart);
	return *this;
}

void StaticPart::makeHtml(std::ostream& html)
{
	for (auto token : tokenList)
	{
		switch (token.type) {
		case Token::html:
			html << token.contens;
			break;
		case Token::part:
			if (containingParts.find(token.partID) != containingParts.end())
			{
				containingParts.at(token.partID)->makeHtml(html);
			}
			break;
		}
	}

}

std::vector<Part*> StaticPart::getAllParts()
{
	std::vector<Part*> retVal;

	for (auto part : containingParts)
	{
		retVal.push_back(part.second);
	}

	retVal.push_back(this);
	return retVal;
}

uint32_t StaticPart::getUniqueIdentifier()
{
	return uint32_t(partId) << 16;
}
