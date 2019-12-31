#pragma once
#include "Controller.h"
#include "html.generated.h"

class TwoController :public Controller
{
public:
	// Inherited via Controller
	//virtual CasResponse makeHTML(CasRequest request) override;
	TwoController()
	{
		partstructure = new PartApp();
		partstructure->addSubpart(PartApp::content, new Parttwo());

	}
};

