#pragma once
#include "Controller.h"
#include "casTypes.h"
#include "../../engine/Resources.h"


class Error404Controller: public Controller
{
	// Inherited via Controller
	virtual void onRequest(CasRequest& request, Poco::Net::HTTPServerResponse& response) override
	{
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND, "Not Found");
		response.setContentType("text/html");
		response.send() << "404 - Site not found";
	}
};

