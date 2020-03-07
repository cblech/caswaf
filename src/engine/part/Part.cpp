#include "Part.h"


Part::Fragment::~Fragment()
{
	switch (type) {
	case none:

		break;
	case html:
		//delete &content;
		
		break;
	case part:
		break;
	default:;
	}
}

Part::Fragment::Fragment(const Fragment& f) :type(f.getType())
{
	switch (type) {
	case none:

		break;
	case html:
		new(&content) std::string;
		content = f.getContent();
		break;
	case part:
		setPluginPoint(f.getPluginPoint());
		break;
	default:;
	}
}

bool Part::Fragment::operator==(Fragment other)
{
	if (this->getType() == none && other.getType() == none)
		return true;
	else
		return this == &other;
}

Part::Part() = default;


Part::Fragment Part::Fragment::nullFragment;


