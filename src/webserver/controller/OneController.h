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
		auto root = new PartApp();
		root->addSubpart(PartApp::PartPluginPoints::content, new Partone());

		partStructure = root;

		
	}
};

