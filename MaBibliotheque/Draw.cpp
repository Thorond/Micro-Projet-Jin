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

	sf::Font font;
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		// error...
	}
	
	while (window.isOpen())
	{
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
					if (route.get_etat() == en_jeu) {
						if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up) {
							route.changer_de_voie_haut_joueur();
						}
						else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
							route.changer_de_voie_bas_joueur();
						}
						else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
							Joueur* voiture_joueur = (Joueur*)route.get_vehicule(route.get_position_voiture_joueur(), route.get_index_voiture_joueur());
							if (voiture_joueur->get_vitesse_x() < VITESSE_MAX_RELATIVE
								&& voiture_joueur->get_x() + LONGUEUR_VOITURE < WINDOW_WIDTH) {
								voiture_joueur->set_vitesse_x(voiture_joueur->get_vitesse_x() + 1);
							}
						}
						else if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Left) {
							Joueur* voiture_joueur = (Joueur*)route.get_vehicule(route.get_position_voiture_joueur(), route.get_index_voiture_joueur());
							if (voiture_joueur->get_vitesse_x() > VITESSE_MIN_RELATIVE
								&& voiture_joueur->get_x() - LONGUEUR_VOITURE > 0) {
								voiture_joueur->set_vitesse_x(voiture_joueur->get_vitesse_x() - 2);
							}
						}
					}
					else if (route.get_etat() == gameover) {
						if (event.key.code == sf::Keyboard::Return) {
							route.set_etat(en_jeu);
							Joueur* voiture_joueur = (Joueur*)route.get_vehicule(route.get_position_voiture_joueur(), route.get_index_voiture_joueur());
							voiture_joueur->set_etat_pc_arriere(abime);
							voiture_joueur->set_etat_pc_avant(abime);
						}
					}
					break;


				default:
				break;
			}
			
		}
		this->clean();
		if (route.get_etat() == en_jeu) {
			sf::Time elapsed = clock.getElapsedTime();
			route.gestion_global(clock, elapsed, window);
		}
		else if (route.get_etat() == gameover) { // temporaire

			sf::Text text;
			text.setFont(font);
			text.setString("GameOver");
			text.setFillColor(sf::Color::Black);
			text.setCharacterSize(50);
			text.setStyle(sf::Text::Bold | sf::Text::Underlined);
			text.setPosition(WINDOW_WIDTH * 3/8 , WINDOW_HEIGHT / 3);


			sf::Text text2;
			text2.setFont(font);
			text2.setString("Appuyez sur 'entrée' pour continuer");
			text2.setFillColor(sf::Color::Black); 
			text2.setCharacterSize(24);
			text2.setPosition(WINDOW_WIDTH *5/16 , WINDOW_HEIGHT * 5/8);

			window.draw(text);
			window.draw(text2);
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