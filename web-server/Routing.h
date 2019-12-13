#pragma once
#include "RoutingEngine.h"
#include "RootController.h"
#include "Error404Controller.h"


class Routing:public RoutingEngine
{
public:
	Routing() {
		setError404Controller(new Error404Controller());

		addRoute(new Route("/",new RootController()));
		addRoute(new Route("/one",new RootController()));
		addRoute(new Route("/one/one",new RootController()));
		addRoute(new Route("/two",new RootController()));
		addRoute(new Route("/two/*/bobo",new RootController()));
	}
};

