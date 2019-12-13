#pragma once
#include <vector>
#include "Route.h"
#include "webserver.h"

class RoutingEngine
{
public:
	~RoutingEngine();


	void processRequest(webserver::http_request* r);

protected:
	void addRoute(Route * r); 
	void setError404Controller(Controller* c);

private:
	
	std::vector<Route*> routes;
	Controller* error404Controller;

	Route* matchPathToRoute(std::string path);
};

