#include "Controller.h"
#include <iostream>

void Controller::onRequest(CasRequest& request, HTTPServerResponse& response)
{
	handlePartRequest(request, response);
}

void Controller::handlePartRequest(CasRequest& request, HTTPServerResponse& response)
{
	//response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK,"OK");
	response.setContentType("text/html");
	rootPart->makeHtml(response.send());
}

/*
void Controller::PartStructure::setup(Part * p)
{
	rootPart = p;
}

Part * Controller::PartStructure::getRootPart()
{
	return rootPart;
}

Controller::PartStructure& Controller::PartStructure::operator=(Part * p)
{
	setup(p);
	return *this;
}
*/
