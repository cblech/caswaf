#include "UsernamePart.h"


R::Part::UsernamePart::UsernamePart(std::string name):name(name),f(Fragment(name))
{
}

/*
void R::Part::UsernamePart::makeHtml(std::ostream& html, InlineParts inlineParts)
{
	html << name;
}
*/

//Part* R::Part::UsernamePart::make()
//{
//	return new UsernamePart(*this);
//}

Part::Fragment* R::Part::UsernamePart::getFragment(int index)
{
	if (index != 0)
		return &Part::Fragment::nullFragment;
	
	return &f;
}



