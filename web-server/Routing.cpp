#include "Routing.h"
#include "../generated/StaticRecouces.h"

Routing::Routing()
{

	setError404Controller(new Error404Controller());

	//static Routes
	addRoute(new Route("/style.css", StaticResources::style_css));
	addRoute(new Route("/bootstrap.css", StaticResources::bootstrap_css));
	addRoute(new Route("/bootstrap.css.map", StaticResources::bootstrap_css_map));
	addRoute(new Route("/pic.png", StaticResources::Pic_png));
	addRoute(new Route("/favicon.ico", StaticResources::caswaf_png));
	addRoute(new Route("/huhu", StaticResources::fu_txt));

	//html Routes
	addRoute(new Route("/", new RootController()));
	addRoute(new Route("/one", new RootController()));
	addRoute(new Route("/one/one", new RootController()));
	addRoute(new Route("/two", new RootController()));
	addRoute(new Route("/two/*/bobo", new RootController()));

}
