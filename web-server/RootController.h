#pragma once
#include "Controller.h"
#include "..\generated\html\App.html.h"
#include "..\generated\html\content\one.html.h"

class RootController :public Controller
{
public:
	// Inherited via Controller
	//virtual CasResponse makeHTML(CasRequest request) override;
	RootController()
	{
		partstructure = new PartApp();
		partstructure->addSubpart(PartApp::content, new Partone());
		
	}
};

