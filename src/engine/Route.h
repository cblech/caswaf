#pragma once
#include <string>
#include "Controller.h"
#include "casTypes.h"
#include "StaticController.h"

class Route
{
public:
	Route(std::string path,Controller* controller);
	Route(std::string path,Resource res);
	~Route();

	std::string getPath();
	void executeController(CasRequest& request, Poco::Net::HTTPServerResponse& response);

private:
	std::string path;
	Controller* controller;
};

