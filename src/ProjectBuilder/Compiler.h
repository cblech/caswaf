#pragma once
#include <list>
#include <boost/filesystem.hpp>
#include "HTMLParser.h"
#include "ProjectStructure.h"


namespace fs = boost::filesystem;
using fs::path;
using std::string;


enum htmlTokenType {none, html, part, /*data*/};
struct htmlToken
{
	htmlToken(htmlTokenType type, string text) :type(type), text(text) {}
	htmlToken(htmlTokenType type, string text,int ppId) :type(type), text(text),ppId(ppId) {}
	htmlTokenType type;
	string text;
	int ppId = 0;
};

class Compiler
{
public:
	Compiler(path resourcesPath, path generatedPath);

	void actionCompileHTML();
	void actionCompileSingleHTML(path pathToFile);
	void actionCompileStatic();
	void actionCompileSingleStatic(path pathToFile);
	void actionCompileConfig();

	void scanAllFilesAndUpdateCache(path p = "resources/html");
	void compileParts();
	
private:
	ProjectStructure projectStructure;
	
	path generatedPath;
	path resoucesPath;
	std::list<path> allGenerated; //lists all HTML Resourcepaths

	//uint16_t partCount = 1;

	
	//Compile HTML Resources to .h files
	//bool compileHtmlFolder(path p);
	//bool compileHtmlFile(path p);

	void htmlNodesToHtmlToken(const HTMLNodeList & nodes, std::list<htmlToken> & tokens, string & tokenWrite, std::map<std::string, int> &  pluginPoints, int & pluginCount);

	//Compile Static Resources to .h files
	bool compileStaticFolder(path p);
	void compileStaticFile(path p, std::iostream & stcInitialStream, std::iostream & stcNameStream, bool writeDataIntoGenerated = false);
};

