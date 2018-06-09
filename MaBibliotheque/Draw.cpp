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
						event_en_jeu(route, event);
					}
					else if (route.get_etat() == gameover) {
						event_game_over(route, event);
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