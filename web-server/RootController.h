#pragma once
#include "Controller.h"
#include "html.generated.h"

class RootController :public Controller
{
public:
	// Inherited via Controller
	//virtual CasResponse makeHTML(CasRequest request) override;
	RootController()
	{
		partstructure = new PartApp();
		partstructure->addSubpart(PartApp::content, new Partroot());
	}
};

