#include "ProjectStructure.h"

#include <string>


#include "Compiler.h"
#include "log.h"

ProjectStructure::ProjectStructure()
{
	int result = sqlite3_open("projectBuilder.cache", &db);
	if (result)
	{
		error << "Error in DB Open: " << sqlite3_errmsg(db);
	}
	populateMetadata();
}

ProjectStructure::~ProjectStructure()
{
	sqlite3_close(db);
}

int ProjectStructure::addPart(const std::string& name, const fs::path& path)
{

	dbExec("INSERT OR REPLACE INTO Parts(name,path,last_modified ) VALUES ('" + name + "','" + path.string() + "'," + std::to_string(fs::last_write_time(path)) + ");");
	int i;
	dbExec("SELECT id FROM Parts WHERE name = '" + name + "';", returnFirstIntCallback, &i);
	return i;
}

int ProjectStructure::addPluginPoint(const std::string& ppName, const int& partId)
{
	dbExec("INSERT OR IGNORE INTO PartPluginPoints(name) VALUES('" + ppName + "');");

	int ppId;
	dbExec("SELECT id, name FROM PartPluginPoints WHERE name = '" + ppName + "';", returnFirstIntCallback, &ppId);

	dbExec(std::string("INSERT OR IGNORE INTO PartsToPluginPoints(fk_Parts_id, fk_PartPluginPoints_id) VALUES (") + std::to_string(partId) + "," + std::to_string(ppId) + ");");

	return ppId;
}

void ProjectStructure::addTokenToPart(const int& pos, const int& partId, const htmlToken& token)
{
	int ppID = 0;
	if (token.type == part)
	{
		ppID = addPluginPoint(token.text, partId);
	}

	dbExec("INSERT OR REPLACE INTO PartTokens(pos,fk_Parts_id,text,type,fk_PartPluginPoint_id)"
		"VALUES(" + std::to_string(pos) + ", " + std::to_string(partId) + ", '" + token.text + "', " + std::to_string(token.type) + ", " + std::to_string(ppID) + "); ");
}

int ProjectStructure::getPluginPoint(std::string name)
{
	throw std::exception("Feature not supported yet!");
}

std::string ProjectStructure::getPluginPointName(int index)
{
	throw std::exception("Feature not supported yet!");
}

std::map<int, ProjectStructure::PartRepresentation> ProjectStructure::getPartsForBuild() const
{
	std::map<int, ProjectStructure::PartRepresentation> retVal;
	std::string sqlParts = "SELECT id,name,path FROM Parts;";
	sqlite3_stmt* stmtParts;
	sqlite3_prepare_v2(db, sqlParts.data(), sqlParts.size(), &stmtParts, nullptr);
	while (sqlite3_step(stmtParts) != SQLITE_DONE)
	{

		int id = sqlite3_column_int(stmtParts, 0);
		std::string name = std::string((char*)sqlite3_column_text(stmtParts, 1));
		std::string path = std::string((char*)sqlite3_column_text(stmtParts, 2));

		retVal.emplace(id, PartRepresentation(id, name, path));
	}

	sqlite3_finalize(stmtParts);


	std::string sqlTokens = "SELECT PT.pos,Parts.id,PT.text,PT.type,PT.fk_PartPluginPoint_id as pluginpoint FROM Parts "
		"LEFT JOIN PartTokens PT on Parts.id = PT.fk_Parts_id ORDER BY pos ASC;";
	sqlite3_stmt* stmtTokens;
	if(sqlite3_prepare_v2(db, sqlTokens.data(), sqlTokens.size(), &stmtTokens, nullptr))
	{
		error << sqlite3_errmsg(db);
	}
	while (sqlite3_step(stmtTokens) != SQLITE_DONE)
	{
		int pos = sqlite3_column_int(stmtTokens, 0);
		int id = sqlite3_column_int(stmtTokens, 1);
		std::string text = std::string((char*)sqlite3_column_text(stmtTokens, 2));
		htmlTokenType type = htmlTokenType(sqlite3_column_int(stmtTokens, 3));
		int pluginpoint = sqlite3_column_int(stmtTokens, 4);

		htmlToken token( type,text,pluginpoint );

		retVal.at(id).token.push_back(token);
	}

	sqlite3_finalize(stmtTokens);



	return retVal;
}

std::vector<ProjectStructure::PluginpointRepresentation> ProjectStructure::getPluginPoints()
{
	std::vector<ProjectStructure::PluginpointRepresentation> retVal;
	std::string sqlParts = "SELECT id,name FROM PartPluginPoints; ";
	sqlite3_stmt* stmtParts;
	sqlite3_prepare_v2(db, sqlParts.data(), sqlParts.size(), &stmtParts, nullptr);
	while (sqlite3_step(stmtParts) != SQLITE_DONE)
	{

		int id = sqlite3_column_int(stmtParts, 0);
		std::string name = std::string((char*)sqlite3_column_text(stmtParts, 1));
		
		retVal.emplace_back(PluginpointRepresentation{ id, name });
	}

	sqlite3_finalize(stmtParts);
	return retVal;
}

void ProjectStructure::populateMetadata()
{
	for (int i = 0; i < 3; ++i)
	{
		try
		{
			dbExec("SELECT * FROM meta;", &populateMetadataCallback, &dbMetaData);
			if (dbMetaData.at("version") != DB_VERSION)
			{
				recreate();
			}

			return;
		}
		catch (DbExecErrorException e)
		{
			recreate();
		}
	}
}

int ProjectStructure::populateMetadataCallback(void* dbMetaData, int colCount, char** value, char** colName)
{
	auto castedData = reinterpret_cast<std::map<std::string, std::string>*>(dbMetaData);
	if (colCount != 2)
		return 1;

	castedData->emplace(value[0], value[1]);

	return 0;

}

int ProjectStructure::returnFirstIntCallback(void* retruned, int colCount, char** value, char** colName)
{
	auto x = (int*)retruned;
	*x = std::stoi(*value);
	return 0;
}

void ProjectStructure::recreate()
{
	dbExec("DROP TABLE IF EXISTS meta;");
	dbExec("CREATE TABLE meta(m_key TEXT PRIMARY KEY,m_value TEXT NOT NULL);");
	dbExec(std::string("INSERT INTO meta (m_key,m_value) VALUES ('version',") + DB_VERSION + "),('type','projectbuildercache')");

	dbExec("DROP TABLE IF EXISTS PartTokens;DROP TABLE IF EXISTS PartsToPluginPoints;DROP TABLE IF EXISTS PartPluginPoints;	DROP TABLE IF EXISTS Parts;"
		"CREATE TABLE Parts(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL UNIQUE,path TEXT NOT NULL, last_modified INTEGER NOT NULL);"
		"CREATE TABLE PartPluginPoints(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL unique);"
		"CREATE TABLE PartsToPluginPoints(fk_Parts_id INTEGER, fk_PartPluginPoints_id INTEGER,FOREIGN KEY(fk_Parts_id) "
		"REFERENCES Parts(id) ON DELETE CASCADE ON UPDATE CASCADE,FOREIGN KEY(fk_PartPluginPoints_id) REFERENCES PartPluginPoints(id) ON DELETE CASCADE ON UPDATE CASCADE ,PRIMARY KEY(fk_Parts_id, fk_PartPluginPoints_id));"

		"CREATE TABLE PartTokens(pos INTEGER,fk_Parts_id INTEGER,text TEXT NOT NULL,type INTEGER NOT NULL ,fk_PartPluginPoint_id INTEGER,"
		"PRIMARY KEY(pos, fk_Parts_id),FOREIGN KEY(fk_Parts_id) REFERENCES Parts(id)  ON DELETE CASCADE ON UPDATE CASCADE, FOREIGN KEY(fk_PartPluginPoint_id) REFERENCES PartPluginPoints(id) ON DELETE CASCADE ON UPDATE CASCADE);");
}

void ProjectStructure::dbExec(std::string query, int (*callback)(void*, int, char**, char**), void* extraData)
{
	sqlite3_stmt* stmt;

	char* msg;
	int result = sqlite3_exec(db, query.data(), callback, extraData, &msg);
	if (result)
	{
		error << "Error in DB Exec: " << msg;
		throw DbExecErrorException("Error in DB Exec");
	}
}
