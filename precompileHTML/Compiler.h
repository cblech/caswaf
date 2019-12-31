#pragma once
#include <list>
#include <boost/filesystem.hpp>


namespace fs = boost::filesystem;
using fs::path;
using std::string;


enum htmlTokenType {none, html, part };
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


	bool compileStatic(path p);
	std::string compileStaticFile(path p);
};

