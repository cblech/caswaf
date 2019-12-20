#include <string>
#include <boost/filesystem.hpp>
#include "Compiler.h"
#include "log.h"



using namespace std;

namespace fs = boost::filesystem;



int main(int argc, char* argv[])
{
	try {
		if (argv[argc - 2] != nullptr && argv[argc - 1] != nullptr)
		{

			fs::path htmlPath = fs::path(argv[argc - 2]);
			fs::path generatedPath = fs::path(argv[argc - 1]);

			if (!fs::is_directory(generatedPath))
			{
				fs::create_directories(generatedPath);
			}

			Compiler c(htmlPath, generatedPath);
		}

	}
	catch (...)
	{
		error << "source and destination directory needed.";
		return 3;
	}


	return 0;
}

