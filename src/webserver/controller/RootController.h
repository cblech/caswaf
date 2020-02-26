#pragma once
#include "Controller.h"
#include "../generated/html.generated.h"
#include "../engine/Resources.h"


class RootController :public Controller
{
public:
	// Inherited via Controller
	//virtual CasResponse makeHTML(CasRequest request) override;
	RootController()
	{
		rootPart = R::Parts::PartApp()
			.addSubpart(R::Parts::PartApp::PartPluginPoints::content, R::Parts::Partroot().make())
			.make();
	}

};

