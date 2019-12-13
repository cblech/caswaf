#pragma once
struct CasRequest {
	std::string method;
	std::string path;
};
struct CasResponse {
	std::string returnCode = "200 - OK";
	std::string content;
};