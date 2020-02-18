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
		partstructure = new PartApp();
		partstructure->addSubpart(PartApp::content, new Partone());
	}
};

