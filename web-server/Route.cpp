#include "Route.h"

Route::Route(std::string path, Controller* controller):path(path),controller(controller)
{
	int i = 0;
}

Route::Route(std::string path, Resource res):path(path),controller(new StaticController(res))
{
	int i = 0;
}

Route::~Route()
{
	if(controller != nullptr)
		delete controller;
}

std::string Route::getPath()
{
	return path;
}

CasResponse Route::executeController(CasRequest request)
{
	return controller->onRequest(request);
}
