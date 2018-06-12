#include "stdafx.h"
#include "monMain.h"

int monMain()
{
	/* Ouverture de la DB*/
	SQLite sqlite = SQLite();
	if (sqlite.get_rc()) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(sqlite.get_db()));
		sqlite3_close(sqlite.get_db());
		return(1);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}
	/* Creation de la classe qui va gerer tout le jeu */
	Route route = Route();
	//sqlite.update_op(0);
	sqlite.select_op(route); // recuperation des données de la DB 

	/* Classe affichage et gestion de la boucle infini du jeu*/
	SFML_output out;
	out.display(route);

	/* Fermeture du jeu et sauvegarde */
	std::cout << route.get_niveau() << std::endl;
	sqlite.update_op(route.get_niveau());
	sqlite3_close(sqlite.get_db());

	return 0;
}