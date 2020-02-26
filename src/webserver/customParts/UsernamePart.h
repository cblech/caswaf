#include "engine/part/DataPart.h"

namespace R::Part
{
	class UsernamePart :public DataPart
	{
	public:
		void makeHtml(std::ostream& html) override;
		Part* make() override;
	};
}