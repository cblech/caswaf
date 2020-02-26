#pragma once
#include "engine/part/DataPart.h"

namespace R::Part
{
	class PathPart :public DataPart
	{
	public:
		struct Data
		{
			std::string path;
		};
		void makeHtml(std::ostream& html) override;
		Part* make() override;
	};
}