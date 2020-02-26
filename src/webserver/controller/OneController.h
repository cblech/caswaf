#pragma once
#include "Controller.h"
#include "../generated/html.generated.h"
#include "../engine/Resources.h"
#include "webserver/customParts/PathPart.h"
#include "webserver/customParts/UsernamePart.h"

class OneController :public Controller
{
public:
	// Inherited via Controller
	//virtual CasResponse makeHTML(CasRequest request) override;
	OneController()
	{
		rootPart = R::Part::PartApp()
			.addSubpart(R::Part::PartApp::PartPluginPoints::content, R::Part::Partone()
				.addSubpart(R::Part::Partone::PartPluginPoints::p1, R::Part::Partroot().make())
				.addSubpart(R::Part::Partone::PartPluginPoints::p2, R::Part::PathPart().make())
				.make())
			.addSubpart(R::Part::PartApp::PartPluginPoints::username, R::Part::UsernamePart().make())
			.make();
	}


	void onRequest(CasRequest& request, HTTPServerResponse& response) override
	{
		R::Part::PathPart::Data d{ request.path};
		
		
		
		handlePartRequest(request,response);
	}
};
