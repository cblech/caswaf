#pragma once
#include <list>
#include <boost/filesystem.hpp>
#include "HTMLParser.h"


namespace fs = boost::filesystem;
using fs::path;
using std::string;


enum htmlTokenType {none, html, part, data};
struct htmlToken
{
	htmlToken(htmlTokenType type, string text) :type(type), text(text) {}
	htmlTokenType type;
	string text;
};

class Compiler
{
public:
	Compiler(path htmlPath, path generatedPath);


private:
	path generatedPath;
	path htmlPath;
	std::list<path> allGenerated;

	bool compilePath(path p);
	bool compileFile(path p);


	void htmlNodesToHtmlToken(const HTMLNodeList & nodes, std::list<htmlToken> & tokens, string & tokenWrite, std::map<std::string, int> &  pluginPoints, int & pluginCount, std::map<std::string,int>& dataPoints , int & dataCount );

	bool compileStatic(path p);
	std::string compileStaticFile(path p);
};

