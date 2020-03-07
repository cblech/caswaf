#pragma once
#include "Controller.h"
#include "casTypes.h"
#include "../../engine/Resources.h"


class Error404Controller: public Controller
{
public:
	Error404Controller()
	{
		root = R::Part::statusdogs();
	}
	
	// Inherited via Controller
	void onRequest(CasRequest& request, Poco::Net::HTTPServerResponse& response) override
	{
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND, "Not Found");
		root.onRequest(request, response);
		//handlePartRequest(request, response);
	}
private:

	PartStructure root;
};

