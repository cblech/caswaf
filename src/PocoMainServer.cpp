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
#include "Routing.h"
#include "Resources.h"

using namespace Poco::Net;
using namespace Poco::Util;
using namespace std;

class MyRequestHandler : public HTTPRequestHandler
{
public:
    virtual void handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
    {
        routing.processRequest(req, resp);

        //resp.send()<<"Hello CMake caswaf";
        cout << "Requested Paht: " << req.getURI()<<"\n\tresponse Status: "<<resp.getStatus()<<" - "<<resp.getReason()<<endl;
    }

private:

    static Routing routing;
    
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
    return app.run(argc, argv);
}

