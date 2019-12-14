#pragma once
#include <string>
#include <map>

struct CasRequest {
	std::string method;
	std::string path;
	std::map<std::string, std::string> params;

	std::string accept;
	std::string accept_language;
	std::string accept_encoding;
	std::string user_agent;
};
struct CasResponse {
	std::string returnCode = "200 - OK";
	std::string content;
};