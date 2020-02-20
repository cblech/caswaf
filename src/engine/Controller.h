#pragma once
#include <string>
#include "casTypes.h"
#include "part/Part.h"
#include "Poco/Net/HTTPResponse.h"

using Poco::Net::HTTPResponse;

class Controller
{
public:
	virtual void onRequest(CasRequest& request, Poco::Net::HTTPServerResponse& response);
	virtual void makeHTML(CasRequest& request, std::ostream& html);

protected:
	Part partstructure;
};

