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
		partstructure = PartApp()
			.addSubpart(PartApp::PartPluginPoints::content, Partone()
			    .addSubpart(Partone::PartPluginPoints::p1,Partroot())
			    .addSubpart(Partone::PartPluginPoints::p2,Partone()
			        .addSubpart(Partone::PartPluginPoints::p2,Partroot())
			    )
			    .addSubpart(Partone::PartPluginPoints::p3,Partroot())
			);
	}
};

