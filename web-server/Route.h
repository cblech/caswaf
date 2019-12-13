#pragma once
#include <string>
#include "Controller.h"
#include "casTypes.h"

class Route
{
public:
	Route(std::string path,Controller* controller);
	~Route();

	std::string getPath();
	CasResponse executeController(CasRequest request);

private:
	std::string path;
	Controller* controller;
};

