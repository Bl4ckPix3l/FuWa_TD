#include "Database.h";


static int callback(void *data, int argc, char **argv, char **azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);
	for (i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

Database::Database(){
	
}

void Database::openConnection(){
	/* Open database */
	rc = sqlite3_open(dbFile, &db);
	if (rc){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else{
		fprintf(stdout, "Opened database successfully\n");
	}
}

void Database::sendQuery(char* query){
	openConnection();
	sqlite3_close(db);

	/* Execute SQL statement */
	rc = sqlite3_exec(db, query, callback, (void*)data, &zErrMsg);
	closeConnection();
}

void Database::closeConnection(){
	sqlite3_close(db);
}

bool Database::checkQuery(){
	if (rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return false;
	}
	else{
		fprintf(stdout, "Operation done successfully\n");
		return true;
	}
}
