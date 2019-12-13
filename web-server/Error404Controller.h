#pragma once
#include "Controller.h"
#include "casTypes.h"


class Error404Controller: public Controller
{
	// Inherited via Controller
	virtual CasResponse makeHTML(CasRequest request) override;
};

