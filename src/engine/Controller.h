#pragma once
#include <string>
#include "casTypes.h"
#include "generated/html/one.html.h"
#include "part/Part.h"
#include "Poco/Net/HTTPResponse.h"

using Poco::Net::HTTPServerResponse;

class Controller
{
public:
	virtual void onRequest(CasRequest& request, HTTPServerResponse& response);

	virtual void handlePartRequest(CasRequest& request, HTTPServerResponse& response);

protected:
	Part * rootPart = nullptr;
};
