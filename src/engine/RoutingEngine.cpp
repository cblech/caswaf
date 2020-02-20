#include "RoutingEngine.h"
#include "starStringEquals.h"
#include <iostream>

void RoutingEngine::processRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
{

	Route* route = matchPathToRoute(req.getURI());


	//Build request
	CasRequest casReq;
	casReq.path = req.getURI();
	casReq.method = req.getMethod();

	casReq.accept = "";
	casReq.accept_language = "";
	casReq.accept_encoding = req.getTransferEncoding();
	casReq.user_agent = req.get("User-Agent");

	//Prepare response
	//CasResponse response;
	//response.content = &resp.send();

	if (route == nullptr)
	{
		error404Controller->onRequest(casReq, resp);
	}
	else
	{
		route->executeController(casReq, resp);
	}

	//resp.send().flush();
	
	/*
	resp.setStatus((HTTPResponse::HTTPStatus)response.statusCode);
	resp.setReason(response.statusMessage);
	resp.setContentType(response.contentType);
	resp.send().flush();
	*/
	
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

Route* RoutingEngine::matchPathToRoute(const std::string& path)
{
	for (Route* rt : routes) {


		if (starstring(rt->getPath()).equals(path))
		{
			return rt;
		}
	}
	return nullptr;
}
