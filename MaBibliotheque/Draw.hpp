#pragma once
#include "EnumEtDonnees.hpp"
#include "EventHandler.hpp"

class SFML_output
{
public:
	SFML_output();
	void display(Route& route);
	void clean();/* Fonction permettant de nettoyer la fenetre */
	/* Fonction generatrice pour l'affichage de texte*/
	void affichage_text(sf::Font& font, sf::String string, int size_char, bool bold, bool underlined, float pos_x, float pos_y);
	void affichage_pause(Route& route, sf::Font& font, bool pause);
	void affichage_game_over(Route& route, sf::Font& font);
	void affichage_donnees_joueur_en_jeu(Route& route, sf::Font& font);
	void affichage_menu_demarrer(Route& route, sf::Font& font);

	sf::RenderWindow& get_window();

private:
	sf::RenderWindow window;
};