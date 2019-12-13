#include "RoutingEngine.h"
#include "webserver.h"
#include "starStringEquals.h"

void RoutingEngine::processRequest(webserver::http_request* request)
{

	request->answer_ = "";

	Route* route = matchPathToRoute(request->path_);


	//Build request
	CasRequest casReq;
	casReq.path = request->path_;
	casReq.method = request->method_;


	//Prepare response
	CasResponse response;

	if (route == nullptr)
	{
		response = error404Controller->makeHTML(casReq);
	}
	else
	{
		response = route->executeController(casReq);
	}

	request->answer_ = response.content;
	request->status_ = response.returnCode;

}

RoutingEngine::~RoutingEngine()
{
	for (Route * r : routes) {
		delete r;
	}
}

void RoutingEngine::addRoute(Route * r)
{
	routes.push_back(r);
}

void RoutingEngine::setError404Controller(Controller* c)
{
	error404Controller = c;
}

Route* RoutingEngine::matchPathToRoute(std::string path)
{
	for (Route* rt : routes) {


		if (starstring(rt->getPath()).equals(path))
		{
			return rt;
		}
	}
	return nullptr;
}
