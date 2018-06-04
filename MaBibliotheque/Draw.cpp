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
						if ( route.get_position_voiture_joueur() == milieu )
							route.changer_de_voie(haute, milieu, 
								*route.get_vehicule(route.get_voie_milieu(),
									route.get_index_voiture_joueur()), true);
						else if (route.get_position_voiture_joueur() == basse)
							route.changer_de_voie(milieu, basse,
								*route.get_vehicule(route.get_voie_basse(),
									route.get_index_voiture_joueur()), true);
					}
					else if (event.key.code ==  sf::Keyboard::S || event.key.code ==  sf::Keyboard::Down) {
						if (route.get_position_voiture_joueur() == milieu)
							route.changer_de_voie(basse, milieu,
								*route.get_vehicule(route.get_voie_milieu(),
									route.get_index_voiture_joueur()), true);
						else if (route.get_position_voiture_joueur() == haute)
							route.changer_de_voie(milieu, haute,
								*route.get_vehicule(route.get_voie_haute(),
									route.get_index_voiture_joueur()), true);
					}
					break;


				default:
				break;
			}
			
		}
		window.clear(); 
		sf::Time elapsed = clock.getElapsedTime();
		route.generation_automatique(clock, elapsed);
		route.Update(window);
		route.draw(window);
		window.display();
	}

}

void SFML_output::clean()
{
	window.clear();
	sf::RectangleShape shape(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)));
	shape.setPosition(sf::Vector2f(0, 0));
	shape.setFillColor(sf::Color::Black);
	window.draw(shape);
}


sf::RenderWindow& SFML_output::get_window() {
	return window;
}