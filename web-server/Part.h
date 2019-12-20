#pragma once
#include <string>
#include <vector>
#include <map>
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

	Part(){}
	//Part(Part* part, Part* rest...);

	std::string generateHTML();

	void addSubpart(int connectionPoint, Part* addedPart);

	//enum Type{html,data};

	//bool isHtmlPart();
	//bool isDataPart();
protected:
	//Type type;
	std::vector<Token> tokenList;
	std::map<int, Part*> containingParts;
};

