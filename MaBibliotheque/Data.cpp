#include "Data.hpp"
#include <iostream>

SQLite::SQLite() 
{
	rc = sqlite3_open("Donnees_de_jeu.db", &this->db);
	
}


sqlite3 * SQLite::get_db() { return db; }
char * SQLite::get_err_mse() { return zErrMsg; }
int SQLite::get_rc() { return rc; }

static int callback(void *data, int argc, char **argv, char **azColName) {
	fprintf(stderr, "%s: ", (const char*)data);
	for (unsigned i = 0; i<argc; i++) {
		std::cout << azColName[i] << " = " << argv[i] << std::endl;
	}
	return 0;
}

void SQLite::create_table() {

	const char * sql;
	/* Create SQL statement */
	sql = "CREATE TABLE DATA("  \
		"NIVEAU            INT     NOT NULL  );";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}
}

void SQLite::insert_op() {
	const char * sql;
	/* Create SQL statement */
	sql = "INSERT INTO DATA (NIVEAU) "  \
		"VALUES (1);";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Records created successfully\n");
	}
}

void SQLite::select_op() {
	const char * sql;
	/* Create SQL statement */
	sql = "SELECT * from DATA";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*)warn, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}
}