#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h" 
#include <string>

class Database
{
private:
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Callback function called \n";

	char* dbFile = "database.db";

	void openConnection();
	void closeConnection();
	bool checkQuery();
	void sendQuery(char* query);

public:

	Database();
	~Database();
};
