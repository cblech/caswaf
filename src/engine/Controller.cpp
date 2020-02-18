#include "Controller.h"

CasResponse Controller::onRequest(CasRequest request)
{
	return {
		200,
		"OK",
		makeHTML(request),
		"text/html"
	};
}

std::string Controller::makeHTML(CasRequest request)
{
	return partstructure.generateHTML();
}
