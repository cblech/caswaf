#include <string>
#include <boost/filesystem.hpp>
#include "Compiler.h"
#include <boost/program_options.hpp>
#include "log.h"
#include "HTMLParser.h"
#include <iostream>

auto VERSION_STRING = "0.0.1";

using namespace std;

namespace fs = boost::filesystem;
namespace po = boost::program_options;



int appMain(int argc, char* argv[])
{

	
	fs::path configPath;
	fs::path resourcesPath;
	fs::path generatedPath;

	fs::path onlyPartPath;
	fs::path onlyStaticPath;

	po::options_description genericOptions("Generic options");

	genericOptions.add_options()
		("help,h", "prints this help message and exits")
		("version,v", "prints the version string and exits")
		("parts-only", "recreates only the part files")
		("statics-only", "recreates only the static files")
		("config-only", "recreates only the config files")
		("part,p", po::value<fs::path>(&onlyPartPath), "recreates only the given part (not implemented yet)")
		("static,s", po::value<fs::path>(&onlyStaticPath), "recreates only the given static file (not implemented yet)")
		("config-path", po::value<fs::path>(&configPath)->default_value(fs::path("caswaf.conf")), "specify the path of the \"config\" file")
		;
	

	po::options_description settingsOptions("Settings");
	settingsOptions.add_options()
		("resources-path", po::value<fs::path>(&resourcesPath), "specify the path of the \"resources\" folder")
		("generated-path", po::value<fs::path>(&generatedPath), "specify the path of the \"generated\" folder")
		;


	po::options_description visibleOptions("CASWAF Project builder version: " + std::string(VERSION_STRING) + "\nAvailable options");
	visibleOptions.add(genericOptions).add(settingsOptions);

	po::variables_map vm;
	po::store(po::basic_command_line_parser(argc, argv).options(visibleOptions).allow_unregistered().run(), vm);
	po::notify(vm);


	if (!fs::is_regular_file(configPath))
	{
		error << "No valid caswaf.conf file found. Please execute the projectBuilder in the root folder of the Project or specify a valid config file using the config-path option";
		return 1;
	}

	po::store(po::parse_config_file(configPath.string().data(), settingsOptions, true), vm);
	po::notify(vm);

	//Debug
	info << resourcesPath;
	info << fs::is_directory(resourcesPath);

	//help option -> prints help message and exit
	if (vm.count("help"))
	{
		std::cout << visibleOptions << endl;
		return 0;
	}

	//version option -> prints version string and exit
	if (vm.count("version"))
	{
		std::cout << std::string(VERSION_STRING) << endl;
		return 0;
	}

#define ELSE else
#define IF_OPTION(OPT) if(vm.count(OPT))
#define ELSE_IF_OPTION(OPT) else IF_OPTION(OPT)

	try
	{
		Compiler c(resourcesPath, generatedPath);

		IF_OPTION("parts-only")
		{
			info << "compiling parts only";
			c.actionCompileHTML();
		}
		ELSE_IF_OPTION("statics-only")
		{
			info << "compiling statics only";
			c.actionCompileStatic();
		}
		ELSE_IF_OPTION("config-only")
		{
			info << "compiling config only";
			c.actionCompileConfig();
		}
		ELSE_IF_OPTION("part")
		{
			info << "compiling only part "<< onlyPartPath;
			c.actionCompileSingleHTML(onlyPartPath);
		}
		ELSE_IF_OPTION("static")
		{
			info << "compiling only static " << onlyStaticPath;
			c.actionCompileSingleStatic(onlyStaticPath);
		}
		ELSE
		{
			info << "compiling all";
			c.actionCompileHTML();
			c.actionCompileStatic();
			c.actionCompileConfig();
		}
	}
	catch (std::exception e)
	{
		error << e.what();
		return 1;
	}



	/*
	try {
		if (argv[argc - 2] != nullptr && argv[argc - 1] != nullptr)
		{
			info << "Last two args: " << argv[argc - 2] <<" - "<< argv[argc - 1];

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

	*/
	return 0;
}

int main(int argc, char* argv[])
{
	auto r = appMain(argc, argv);
	//system("pause");
	return r;
}