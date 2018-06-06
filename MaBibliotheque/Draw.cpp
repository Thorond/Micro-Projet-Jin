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
					if (event.key.code == sf::Keyboard::Z || event.key.code ==  sf::Keyboard::Up) {
						route.changer_de_voie_haut_joueur();
					}
					else if (event.key.code ==  sf::Keyboard::S || event.key.code ==  sf::Keyboard::Down) {
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
							voiture_joueur->set_vitesse_x(voiture_joueur->get_vitesse_x() - 1);
						}
					}
					break;


				default:
				break;
			}
			
		}
		this->clean(); 
		sf::Time elapsed = clock.getElapsedTime();
		route.gestion_global(clock, elapsed, window);
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