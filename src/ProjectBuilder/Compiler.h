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
	Compiler(path resourcesPath, path generatedPath);

	void actionCompileHTML();
	void actionCompileStatic();

private:
	path generatedPath;
	path resoucesPath;
	std::list<path> allGenerated; //lists all HTML Resourcepaths


	//Compile HTML Resources to .h files
	bool compilePath(path p);
	bool compileFile(path p);

	void htmlNodesToHtmlToken(const HTMLNodeList & nodes, std::list<htmlToken> & tokens, string & tokenWrite, std::map<std::string, int> &  pluginPoints, int & pluginCount, std::map<std::string,int>& dataPoints , int & dataCount );

	//Compile Static Resources to .h files
	bool compileStatic(path p);
	void compileStaticFile(path p, std::iostream & stcInitialStream, std::iostream & stcNameStream, bool writeDataIntoGenerated = false);
};
