#pragma once
#include "Controller.h"
#include "html.generated.h"

class TwoBoboController :public Controller
{
public:
	// Inherited via Controller
	//virtual CasResponse makeHTML(CasRequest request) override;
	TwoBoboController()
	{
		partstructure = new PartApp();
		partstructure->addSubpart(PartApp::content, new Parttwobobo());

	}


	CasResponse onRequest(CasRequest request) override
	{
		auto res = Controller::onRequest(request);
		res.content += request.path;
		return res;
	}
};

