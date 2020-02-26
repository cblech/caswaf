#pragma once
#include "Controller.h"
#include "../engine/Resources.h"


class RootController :public Controller
{
public:
	// Inherited via Controller
	//virtual CasResponse makeHTML(CasRequest request) override;
	RootController()
	{
		rootPart = R::Part::PartApp()
			.addSubpart(R::Part::PartApp::PartPluginPoints::content, R::Part::Partroot().make())
			.make();

	}
};

