#pragma once
#include "casTypes.h"
#include <list>

class WebPathHandler
{
public:
	WebPathHandler();

	virtual casResponse handleRequest(casRequest req) = 0;
	virtual casResponse handleSubRequest(casRequest req);



	WebPathHandler* addSubHandler(WebPathHandler* subHandler);

	std::list<WebPathHandler*> subHandlerList;

};

