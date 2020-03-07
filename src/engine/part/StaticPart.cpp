#include "StaticPart.h"


//StaticPart::StaticPart(std::vector<PartPlugin> pps)
//{
//}

/*
StaticPart StaticPart::addSubpart(int connectionPoint, Part* addedPart)
{
	containingParts.try_emplace(connectionPoint, addedPart);
	return *this;
}*/

/*
void StaticPart::makeHtml(std::ostream& html, InlineParts inlineParts)
{
	for (auto token : fragmentList)
	{
		switch (token.type) {
		case Token::html:
			html << token.content;
			break;
		case Token::part:
			if (inlineParts.find(token.pluginPoint) != inlineParts.end())
			{
				inlineParts.at(token.pluginPoint)->makeHtml(html);
			}
			break;
		}
	}

}
*/
/*
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
*/

uint32_t StaticPart::getUniqueIdentifier()
{
	return uint32_t(partId) << 16;
}

Part::Fragment* StaticPart::getFragment(int index)
{
	try
	{
		return &fragmentList.at(index);
	}
	catch (...)
	{
		return &Part::Fragment::nullFragment;
	}
}
