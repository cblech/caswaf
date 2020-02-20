#include "Controller.h"
#include <iostream>

void Controller::onRequest(CasRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setStatusAndReason(HTTPResponse::HTTP_OK,"OK");
	response.setContentType("text/html");
	makeHTML(request, response.send());
	
	/*
	return {
		200,
		"OK",
		makeHTML(request),
		"text/html"
	};*/
}

void Controller::makeHTML(CasRequest& request, std::ostream& html)
{
	partstructure.generateHTML(html);
}
