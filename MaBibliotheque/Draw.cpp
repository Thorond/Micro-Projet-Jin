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
		else if (route.get_etat() == gameover) { 
			this->affichage_text(font, "GameOver", 50, true, true, WINDOW_WIDTH * 3 / 8, WINDOW_HEIGHT / 3);
			this->affichage_text(font, "Appuyez sur 'entrée' pour continuer", 24, false, false, WINDOW_WIDTH * 5 / 16, WINDOW_HEIGHT * 5 / 8);
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

void SFML_output::affichage_text(sf::Font& font, sf::String string, int size_char, bool bold, bool underlined, double pos_x, double pos_y) {


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