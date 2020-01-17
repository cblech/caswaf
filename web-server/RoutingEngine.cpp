#include "RoutingEngine.h"
#include "webserver.h"
#include "starStringEquals.h"
#include <iostream>

void RoutingEngine::processRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
{

	

	Route* route = matchPathToRoute(req.getURI());


	//Build request
	CasRequest casReq;
	casReq.path = req.getURI();
	casReq.method = req.getMethod();
	casReq.params;

	casReq.accept = "";
	casReq.accept_language = "";
	casReq.accept_encoding = req.getTransferEncoding();
	casReq.user_agent = req.get("User-Agent");

	//Prepare response
	CasResponse response;

	if (route == nullptr)
	{
		response = error404Controller->onRequest(casReq);
	}
	else
	{
		response = route->executeController(casReq);
	}


	resp.setStatus((HTTPResponse::HTTPStatus)response.statusCode);
	resp.setReason(response.statusMessage);
	resp.setContentType(response.contentType);
	(resp.send() << response.content).flush();

	//request->answer_ = response.content;
	//request->status_ = response.returnCode;
	//request->content_type_ = response.contentType;

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
