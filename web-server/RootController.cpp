#include "RootController.h"
#include <string>
#include "StringExplode.h"

/*
CasResponse RootController::makeHTML(CasRequest request)
{
	CasResponse response;
	auto pathParts = explode(request.path, '/');
	response.content = "Test Content im response.<br>Paht: "+pathParts[1];
	response.content += "<br>Agent: "+request.user_agent;

	return response;
}
*/