#include "RootController.h"
#include <string>


CasResponse RootController::makeHTML(CasRequest request)
{
	CasResponse response;

	response.content = "Test Content im response";

	return response;
}
