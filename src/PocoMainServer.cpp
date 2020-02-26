#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/ServerApplication.h>
#include <iostream>
#include <string>
#include <vector>
#include "Resources.h"
#include "webserver/Routing.h"
#include <Poco/Logger.h>

using namespace Poco::Net;
using namespace Poco::Util;
using namespace std;

class MyRequestHandler : public HTTPRequestHandler
{
public:
   // MyRequestHandler() = default;
	
    virtual void handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
    {
        routing.processRequest(req, resp);
        Poco::Logger& logger = Poco::Logger::get("Requests");

        logger.information(Poco::format("Requested Paht: %s\n    response Status: %d - %s", req.getURI(), static_cast<int>(resp.getStatus()), resp.getReason()));

        //cout << "Requested Paht: " << req.getURI()<<"\n    response Status: "<<resp.getStatus()<<" - "<<resp.getReason()<<endl;
    }

private:

    static Routing routing;
    //Poco::Logger logger;
    
};


AllResources R;
Routing MyRequestHandler::routing;


class MyRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
    virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest&)
    {
        return new MyRequestHandler;
    }
};

class MyServerApp : public ServerApplication
{
protected:
    int main(const vector<string>& args)
    {
        HTTPServer s(new MyRequestHandlerFactory, ServerSocket(80), new HTTPServerParams);

        s.start();
        cout << endl << "Server started" << endl;

        //Sleep(10000);
    	
        waitForTerminationRequest();  // wait for CTRL-C or kill

        cout << endl << "Shutting down..." << endl;
        s.stop();

        return Application::EXIT_OK;
    }
};

int main(int argc, char** argv)
{
    cout << "PocoMain" << endl;
    MyServerApp app;
    int i = app.run(argc, argv);


    return i;
}

