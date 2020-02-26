#pragma once
#include "Controller.h"
#include "../generated/html.generated.h"
#include "../engine/Resources.h"

class OneController :public Controller
{
public:
	// Inherited via Controller
	//virtual CasResponse makeHTML(CasRequest request) override;
	OneController()
	{
		rootPart = R::Parts::PartApp()
			.addSubpart(R::Parts::PartApp::PartPluginPoints::content, R::Parts::Partone()
				.addSubpart(R::Parts::Partone::PartPluginPoints::p1, R::Parts::Partroot().make())
				.make())
			.make();
	}
};
