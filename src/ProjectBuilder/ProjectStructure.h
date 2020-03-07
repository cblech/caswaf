#pragma once

#include <map>
#include <sqlite3.h>
#include <string>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class htmlToken;

#define DB_VERSION "9"

typedef std::exception DbExecErrorException;

class ProjectStructure
{
public:

	struct PartRepresentation
	{
		PartRepresentation(int id, std::string name, std::string path)
			:id(id), name(name), originalPath(path) {};
		int id;
		std::string name;
		fs::path originalPath;
		std::vector<htmlToken> token;
	};
	struct PluginpointRepresentation
	{
		int id;
		std::string name;
	};

	ProjectStructure();
	~ProjectStructure();

	int addPart(const std::string& name, const fs::path& path);
	int addPluginPoint(const std::string& ppName, const int& partId);
	void addTokenToPart(const int& pos, const int& partId, const htmlToken& token);
	int getPluginPoint(std::string name);
	std::string getPluginPointName(int index);
	std::map<int, ProjectStructure::PartRepresentation> getPartsForBuild() const;
	std::vector<PluginpointRepresentation> getPluginPoints();

private:

	void populateMetadata();
	static int populateMetadataCallback(void* Unused, int colCount, char** value, char** colName);
	static int returnFirstIntCallback(void* retruned, int colCount, char** value, char** colName);


	void recreate();

	void dbExec(std::string query, int (*callback)(void*, int, char**, char**) = nullptr, void* extraData = nullptr);

	sqlite3* db;
	std::map<std::string, std::string> dbMetaData;
};
