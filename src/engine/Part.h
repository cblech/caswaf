#pragma once
#include <string>
#include <vector>
#include <map>

class Part;
typedef std::pair<int,Part> PartPlugin;

class Part
{
public:
	struct Token
	{
		enum Type{html,data,part};
		std::string contens;
		Type type;
		int partID;
	};

	Part();
	//Part(PartPlugin pp);
	//Part(Part* part, Part* rest...);

	std::string generateHTML();

protected:
	Part addSubpart(int connectionPoint, Part addedPart);

	//enum Type{html,data};

	//bool isHtmlPart();
	//bool isDataPart();
protected:
	//Type type;
	std::vector<Token> tokenList;
	std::map<int, Part> containingParts;
};

