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
		auto po = new Partone();
		partstructure->addSubpart(PartApp::content,po);
		po->addSubpart(Partone::subcontent, new Partothercontent());
		
	}
};

