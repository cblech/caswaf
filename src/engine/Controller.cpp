#include "Controller.h"
#include <iostream>

void Controller::onRequest(CasRequest& request, HTTPServerResponse& response)
{
	response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK,"OK");
	response.setContentType("text/html");
	partStructure.getRootPart()->makeHtml(response.send());
	/*
	return {
		200,
		"OK",
		makeHTML(request),
		"text/html"
	};*/
}

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
