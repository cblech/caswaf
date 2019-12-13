#pragma once
#include <string>
#include "casTypes.h"

class Controller
{
public:
	virtual CasResponse makeHTML(CasRequest request) = 0;
};

