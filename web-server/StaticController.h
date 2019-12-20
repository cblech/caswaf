#pragma once
#include "Controller.h"
#include <sstream>
#include "StaticRecource.h"

class StaticController: public Controller
{
public:
	StaticController(Resource resource):resource(resource){}

	CasResponse onRequest(CasRequest request) override
	{
		CasResponse cr = Controller::onRequest(request);
		cr.contentType = resource.content_type;
		return cr;
	}

	std::string makeHTML(CasRequest request) override
	{
		std::stringstream ss;

		for (int i = 0; i < resource.data_size;i++)
		{
			ss << resource.data[i];
		}

		return ss.str();
	}
private:
	Resource resource;
};