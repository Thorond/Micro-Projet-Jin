#pragma once
#include <SFML/Graphics.hpp>
class SFML_output
{
public:
	SFML_output();
	void draw_circle(double x, double r);
	void display();
	void clean();

private:
	sf::RenderWindow window;
};