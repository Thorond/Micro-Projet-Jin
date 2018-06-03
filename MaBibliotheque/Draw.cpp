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