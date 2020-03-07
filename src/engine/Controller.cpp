#include "Controller.h"
#include <iostream>

void Controller::onRequest(CasRequest& request, HTTPServerResponse& response)
{
	//handlePartRequest(request, response);
}
/*
void Controller::handlePartRequest(CasRequest& request, HTTPServerResponse& response)
{
	response.setContentType("text/html");
	rootPart->makeHtml(response.send());
}
*/