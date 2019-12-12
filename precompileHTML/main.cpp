#include <string>
#include <boost/filesystem.hpp>
#include "Compiler.h"



using namespace std;

namespace fs = boost::filesystem;



int main(int argc, char* argv[]) 
{

	fs::path htmlPath = fs::path(argv[argc - 2]);
	fs::path generatedPath = fs::path(argv[argc - 1]);

	if (!fs::is_directory(generatedPath))
	{
		fs::create_directories(generatedPath);
	}

	Compiler c(htmlPath,generatedPath);

	return 0;
}

