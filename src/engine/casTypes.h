#pragma once
#include <string>
#include <map>
#include <iostream>
#include <Poco/Net/HTTPServerResponse.h>

struct CasRequest {
	std::string method;
	std::string path;
	std::map<std::string, std::string> params;

	std::string accept;
	std::string accept_language;
	std::string accept_encoding;
	std::string user_agent;


};

/*
struct CasResponse {
	int statusCode=200;
	std::string statusMessage = "OK";
	std::ostream * content;
	std::string contentType = "text/html";
};*/

