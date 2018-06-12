#pragma once
#include <sqlite3.h>
#include "Route.hpp"

class SQLite {
public:
	SQLite();
	sqlite3 * get_db();
	char * get_err_mse();
	int get_rc();
	void create_table(); 
	void insert_op();
	void select_op(Route& route);
	void update_op(int niveau);
	void delete_op();
private:
	sqlite3 * db;
	char *zErrMsg = 0;
	int rc;
	const char* warn = "Callback function called";
};
