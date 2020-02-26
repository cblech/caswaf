#pragma once
#include "PathPart.h"

void R::Part::PathPart::makeHtml(std::ostream& html)
{
	html << "cblech";
}

Part* R::Part::PathPart::make()
{
	return new PathPart(*this);
}


