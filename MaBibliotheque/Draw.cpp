#include "stdafx.h"
#include <string>
#include <vector>
#include "Draw.hpp"



SFML_output::SFML_output()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Outil visualisation")
{
	clean();
}

void SFML_output::display(Route& route)
{
	window.display();
	sf::Clock clock;
	sf::Clock clockBoucle;

	sf::Font font;
	//if (!font.loadFromFile("fonts/Alfredo_.ttf"))
	//{
	//	// error...
	//}
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		// error...
	}

	double lag = 0.0;
	
	while (window.isOpen())
	{
		double elapsedBoucle = clockBoucle.restart().asMilliseconds();
		lag += elapsedBoucle;

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// fenetre fermee
				case sf::Event::Closed:
					window.close() ;
				break;


				// acquisition des evenements touche pressee
				case sf::Event::KeyPressed:
					switch (route.get_etat()) {
					case en_jeu:
						event_en_jeu(route, event);
						break;
					case pause:
						event_pause(route, event);
						break;
					case gameover :
						event_game_over(route, event);
						break;
					case menu_demarrer :
						event_menu_demarrer(route, event);
						break;
					}
					break;


				default:
				break;
			}
			
		}
		this->clean();
		switch (route.get_etat()) {
			case en_jeu:
			{
				while (lag >= MS_PER_UPDATE)
				{
					sf::Time elapsed = clock.getElapsedTime();
					route.gestion_global(clock, elapsed, window);
					lag -= MS_PER_UPDATE;
				}
				route.draw(window);
				this->affichage_donnees_joueur_en_jeu(route, font);
				this->affichage_pause(route, font, false);
				break;
			}
			case pause:
			{
				this->affichage_donnees_joueur_en_jeu(route, font);
				this->affichage_pause(route, font, true);
				break;
			}
			case gameover :
				this->affichage_game_over(route, font);
				break;
			case menu_demarrer :
				this->affichage_menu_demarrer(route, font);
				break;
		}
		window.display();
	}

}

void SFML_output::clean()
{
	window.clear();
	sf::RectangleShape shape(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)));
	shape.setPosition(sf::Vector2f(0, 0));
	shape.setFillColor(sf::Color::White);
	window.draw(shape);
}


sf::RenderWindow& SFML_output::get_window() {
	return window;
}

void SFML_output::affichage_text(sf::Font& font, sf::String string, int size_char, bool bold, bool underlined, float pos_x, float pos_y) {
	sf::Text text;
	text.setFont(font);
	text.setString(string);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(size_char);
	if (bold) text.setStyle(sf::Text::Bold);
	if ( underlined ) text.setStyle(sf::Text::Underlined);
	text.setPosition(pos_x, pos_y);
	window.draw(text);
}

void SFML_output::affichage_pause(Route& route, sf::Font& font, bool pause) {
	if (!pause) {
		std::string pause = " Pause : 'P' ";
		this->affichage_text(font, pause, 26, false, false, WINDOW_WIDTH * 5 / 6, WINDOW_HEIGHT * 1 / 16);
	}
	else {
		std::string pause = " PAUSE (P)";
		this->affichage_text(font, pause, 26, false, false, WINDOW_WIDTH * 7/16 , WINDOW_HEIGHT /2);
	}
}

void SFML_output::affichage_game_over(Route& route, sf::Font& font) {
	this->affichage_text(font, "GameOver", 60, true, true, WINDOW_WIDTH * 3 / 8, WINDOW_HEIGHT / 3);
	this->affichage_text(font, "Appuyez sur 'entrée' pour continuer", 40, false, false, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 5 / 8);
}

void SFML_output::affichage_donnees_joueur_en_jeu(Route& route, sf::Font& font) {
	Joueur* voiture_joueur = (Joueur*)route.get_vehicule(route.get_position_voiture_joueur(), route.get_index_voiture_joueur());
	std::string vitesse = " Vitesse : " + std::to_string((int)(voiture_joueur->get_vitesse_x() + VITESSE_DEFILEMENT));
	this->affichage_text(font, vitesse , 40, false, false, WINDOW_WIDTH * 3/4, WINDOW_HEIGHT * 7 / 8);
	std::string niveau = " Niveau : " + std::to_string(route.get_niveau() + 1);
	this->affichage_text(font, niveau, 40, false, false, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 6 / 8);
	std::string etat_pc_avant = " Pare-choc avant : " + std::to_string(voiture_joueur->get_etat_pc_avant());
	this->affichage_text(font, etat_pc_avant, 40, false, false, 50, WINDOW_HEIGHT * 6 / 8);
	std::string etat_pc_arriere = " Pare-choc arrière : " + std::to_string(voiture_joueur->get_etat_pc_arriere());
	this->affichage_text(font, etat_pc_arriere, 40, false, false, 50, WINDOW_HEIGHT * 7 / 8);
	std::string distance_parcouru = " Distance parcouru : " + std::to_string(route.get_distance_parcouru()/10) + " mètres.";
	this->affichage_text(font, distance_parcouru, 40, true, false, 50, WINDOW_HEIGHT * 1 / 8);

}

void SFML_output::affichage_menu_demarrer(Route& route, sf::Font& font) {
	this->affichage_text(font, " Bienvenue", 60, true, true, WINDOW_WIDTH * 3 / 8, WINDOW_HEIGHT / 3);
	this->affichage_text(font, "Appuyez sur 'entrée' pour entrer en jeu", 40, false, false, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 5 / 8);

}