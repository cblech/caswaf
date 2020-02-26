#pragma once
#include "Controller.h"
#include "casTypes.h"
#include "../../engine/Resources.h"


class Error404Controller: public Controller
{
public:
	Error404Controller()
	{
		rootPart = R::Part::Partstatusdogs().make();
	}
	
	// Inherited via Controller
	void onRequest(CasRequest& request, Poco::Net::HTTPServerResponse& response) override
	{
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND, "Not Found");
		handlePartRequest(request, response);
	}
};

