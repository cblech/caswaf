#pragma once
#include "Controller.h"
#include <sstream>
#include "StaticRecource.h"

class StaticController: public Controller
{
public:
	StaticController(Resource resource):resource(resource){}

	void onRequest(CasRequest& request, Poco::Net::HTTPServerResponse& response) override
	{
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK, "OK");
		response.setContentType(resource.content_type);
		response.sendBuffer(resource.data.data(), resource.data.size());
	}

private:
	Resource resource;
};