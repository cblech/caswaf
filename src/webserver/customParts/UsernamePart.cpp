#include "UsernamePart.h"

void R::Part::UsernamePart::makeHtml(std::ostream& html)
{
	html << "cblech";
}

Part* R::Part::UsernamePart::make()
{
	return new UsernamePart(*this);
}


