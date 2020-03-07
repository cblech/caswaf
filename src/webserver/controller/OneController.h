#pragma once
#include "Controller.h"
#include "../generated/html.generated.h"
#include "../engine/Resources.h"
#include "PartStructure.h"
#include "webserver/customParts/PathPart.h"
#include "webserver/customParts/UsernamePart.h"

class OneController :public Controller
{
public:
	// Inherited via Controller
	//virtual CasResponse makeHTML(CasRequest request) override;
	OneController()
	{
		/*
		rootPart = R::Part::App()
			.addSubpart(R::PluginPoints::content, R::Part::one()
				.addSubpart(R::PluginPoints::p1, R::Part::root().make())
				.make())
			.addSubpart(R::PluginPoints::username, R::Part::UsernamePart().make());
			*/
		rootStructure = PartStructure(R::Part::App())
			.add(R::PluginPoints::content, R::Part::one());

		
	}


	void onRequest(CasRequest& request, HTTPServerResponse& response) override
	{
		PartStructure cp = rootStructure;
		auto p = &R::Part::UsernamePart(request.path);
		cp.add(R::PluginPoints::username, static_cast<Part*>(p));
		
		cp.onRequest(request, response);
	}
private:
	//R::Part::App rootPart;
	PartStructure rootStructure;
	
};
