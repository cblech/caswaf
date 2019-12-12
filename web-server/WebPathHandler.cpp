#include "webPathHandler.h"

casResponse WebPathHandler::handleSubRequest(casRequest req)
{
	
	return casResponse();
}

WebPathHandler* WebPathHandler::addSubHandler(WebPathHandler* subHandler)
{
	subHandlerList.push_back(subHandler);
	return this;
}
