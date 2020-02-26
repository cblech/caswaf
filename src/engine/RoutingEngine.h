#pragma once
#include <vector>
#include "Route.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

class RoutingEngine
{
public:
	~RoutingEngine();


	void processRequest(HTTPServerRequest& req, HTTPServerResponse& resp);

protected:
	void addRoute(const Route& r); 
	void setError404Controller(Controller* c);

private:
	
	std::vector<Route*> routes;
	Controller* error404Controller=nullptr;

	Route* matchPathToRoute(const std::string& path);
};

