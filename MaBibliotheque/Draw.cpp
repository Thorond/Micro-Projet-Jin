#include "stdafx.h"
#include <string>
#include <vector>
#include "Draw.hpp"

static const unsigned int WINDOW_WIDTH(1000);
static const unsigned int WINDOW_HEIGHT(700);


SFML_output::SFML_output()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Outil visualisation")
{
	clean();
}

void SFML_output::draw_circle(double absolute_x, double r)
{
	sf::CircleShape shape(static_cast<float>(r));
	shape.setFillColor(sf::Color::White);
	shape.setPosition(static_cast<float>(absolute_x + WINDOW_WIDTH / 2 - r), static_cast<float>(WINDOW_HEIGHT / 2 - (50 + r)));
	window.draw(shape);
}

void SFML_output::display()
{
	window.display();
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
		//sf::sleep(sf::milliseconds(1000));
		//window.close();
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