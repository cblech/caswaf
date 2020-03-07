#pragma once
#include "engine/part/DataPart.h"

namespace R::Part
{
	class UsernamePart :public DataPart
	{
	public:
		UsernamePart(std::string name);
		
		//void makeHtml(std::ostream& html, InlineParts inlineParts) override;
		//Part* make() override;

		Fragment* getFragment(int index) override;
	private:
		std::string name;
		Fragment f;
	};
}

