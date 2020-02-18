#include <string>
#include <boost/filesystem.hpp>
#include "Compiler.h"
#include "log.h"
#include "HTMLParser.h"



using namespace std;

namespace fs = boost::filesystem;

int nomain(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++) 
	{
		info << argv[i];
	}
	return 0;
}

int main(int argc, char* argv[])
{
	
	//info << "Testing HTML Parser";

	//auto nl = HTMLParser::parseHTML(R"(<div cute><p id="haiho">parag <br foo="bar"/> blabla</p>hallo</div>)");

	//auto test = HTMLParser::parseNodeFromToken(HTMLParser::Token(HTMLParser::Token::Type::tag, "<  p  \n id    =\"haiho\" bla=\"huhn babera\">"));

	//info << test;
	//info << nl;

	//return 0; // TODO: remove testing

	//system("cd");

	try {
		if (argv[argc - 2] != nullptr && argv[argc - 1] != nullptr)
		{
			info << "Last two args: " << argv[argc - 2] <<" - "<< argv[argc - 1];
			//system("pwd");

            //generate path objects out of the given arguments
			fs::path resourcesPath = fs::path(argv[argc - 2]);
			fs::path generatedPath = fs::path(argv[argc - 1]);

			//create "generated" folder if it doesn't exist yet
			if (!fs::is_directory(generatedPath))
			{
				fs::create_directories(generatedPath);
			}


			Compiler c(resourcesPath, generatedPath);
			c.actionCompileHTML();
			c.actionCompileStatic();
		}

	}
	catch (...)
	{
		error << "source and destination directory needed.";
		return 3;
	}


	return 0;
}

