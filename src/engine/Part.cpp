#include "Part.h"

//bool Part::isHtmlPart()
//{
//	return type == html;
//}
//
//bool Part::isDataPart()
//{
//	return type == data;
//}

//Part::Part(std::vector<Part*> parts)
//{
//	for (Part* p : parts)
//	{
//		containingParts.try_emplace(p->containingParts,p->addSubpart );
//	}
//}

Part::Part()
{
}

//Part::Part(PartPlugin pp)
//{
//	addSubpart(pp.first, pp.second);
//}

std::string Part::generateHTML()
{
	std::string retVal = "";
	for (auto token : tokenList)
	{
		switch (token.type) {
		case Token::html:
			retVal += token.contens;
			break;
		case Token::data:
			//TODO
			break;
		case Token::part:
			if (containingParts.find(token.partID) != containingParts.end())
			{
				retVal += containingParts.at(token.partID).generateHTML();
			}
			break;
		}
	}

	return retVal;
}

Part Part::addSubpart(int connectionPoint, Part addedPart)
{
	containingParts.try_emplace(connectionPoint, addedPart);
	return *this;
}
