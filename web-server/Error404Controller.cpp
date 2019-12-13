#include "Error404Controller.h"
#include "casTypes.h"

CasResponse Error404Controller::makeHTML(CasRequest request)
{
	CasResponse response;

	response.content = "404 - Site not found";
	response.returnCode = "404 - Not found";

	return response;
}
