#include "Routing.h"
#include "../webserver/controller/OneController.h"
#include "controller/Error404Controller.h"
#include "controller/RootController.h"
#include "Resources.h"

Routing::Routing()
{
    setError404Controller(new Error404Controller());

    //static Routes
	
    addRoute( Route("/style.css", R::Static.style_css));

    addRoute( Route("/bootstrap.css", R::Static.bootstrap_css));
    //addRoute(new Route("/bootstrap.css.map", R::Static.bootstrap_css_map));
    addRoute( Route("/pic.png", R::Static.Pic_png));
    addRoute( Route("/favicon.ico", R::Static.caswaf_png));
    addRoute( Route("/huhu", R::Static.fu_txt));

    //html Routes
    addRoute( Route("/", new RootController()));
    addRoute( Route("/one", new OneController()));

}
