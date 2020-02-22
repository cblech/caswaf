#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Part;
typedef std::pair<int,Part *> PartPlugin;

class Part
{
public:
	struct Token
	{
		enum Type{html,part};
		std::string contens;
		Type type;
		int partID;
	};

	Part();

	virtual void makeHtml(std::ostream& html)=0;
	virtual std::vector<Part*> getAllParts()=0;

protected:


};

