#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <iostream>
#include <vector>
#include <map>

#include "SQLLiteWrapper.h"


class Model
{
public: 
	std::vector<std::map<std::string, std::string>*> getWave();
	std::vector<std::map<std::string, std::string>*> getWaves();
	std::vector<std::map<std::string, std::string>*> getEnemys();
	std::vector<std::map<std::string, std::string>*> getTowers();
	std::vector<std::map<std::string, std::string>*> getMaps();
	std::vector<std::map<std::string, std::string>*> getRace();

	std::vector<std::map<std::string, std::string>*> execute(char *query);

private:
	SQLiteDB *pSQLite;

public:

	Model();
	~Model();
};
