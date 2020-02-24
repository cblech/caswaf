#include "Routing.h"
#include "../webserver/controller/AllController.h"
#include "../webserver/controller/OneController.h"
#include "Resources.h"

Routing::Routing()
{
    setError404Controller(new Error404Controller());

    //static Routes
	
    addRoute(new Route("/style.css", R.Static.style_css));

    addRoute(new Route("/bootstrap.css", R.Static.bootstrap_css));
    //addRoute(new Route("/bootstrap.css.map", R.Static.bootstrap_css_map));
    addRoute(new Route("/pic.png", R.Static.Pic_png));
    addRoute(new Route("/favicon.ico", R.Static.caswaf_png));
    addRoute(new Route("/huhu", R.Static.fu_txt));

    //html Routes
    addRoute(new Route("/", new RootController()));
    addRoute(new Route("/one", new OneController()));

}
