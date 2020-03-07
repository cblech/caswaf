#pragma once
#include "Controller.h"
#include "Resources.h"


class RootController :public Controller
{
public:
	// Inherited via Controller
	//virtual CasResponse makeHTML(CasRequest request) override;
	RootController()
	{
		rootPart = PartStructure(R::Part::App())
			.add(R::PluginPoints::content, R::Part::root());
			//.add(R::PluginPoints::username,R::Part::UsernamePart("Test"));

	}

	void onRequest(CasRequest& request, HTTPServerResponse& response) override
	{
		PartStructure cp = rootPart;
		auto p = R::Part::UsernamePart("jonny");
		cp.add(R::PluginPoints::username, static_cast<Part*>(&p));
		cp.onRequest(request, response);
	}

private:
	PartStructure rootPart;
};

