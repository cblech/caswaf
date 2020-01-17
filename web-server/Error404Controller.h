#pragma once
#include "Controller.h"
#include "casTypes.h"


class Error404Controller: public Controller
{
	// Inherited via Controller
	virtual CasResponse onRequest(CasRequest request) override
	{
		return {
			404,
			"Not Found",
			makeHTML(request)
		};
	}
	virtual std::string makeHTML(CasRequest request) override
	{
		return "404 - Site not found";
	}
};

