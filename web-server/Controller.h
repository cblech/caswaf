#pragma once
#include <string>
#include "casTypes.h"
#include "Part.h"

class Controller
{
public:
	virtual CasResponse onRequest(CasRequest request);
	virtual std::string makeHTML(CasRequest request);

protected:
	Part* partstructure;
};

