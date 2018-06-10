#include "stdafx.h"
#include "monMain.h"

int monMain()
{
	SQLite sqlite = SQLite();
	if (sqlite.get_rc()) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(sqlite.get_db()));
		sqlite3_close(sqlite.get_db());
		return(1);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}
	//sqlite.create_table();
	//sqlite.insert_op();
	sqlite.select_op();

	Route route = Route();
	SFML_output out;
	out.display(route);

	sqlite3_close(sqlite.get_db());

	return 0;
}