#pragma once
#include <SFML/Graphics.hpp>
#include "EnumEtDonnees.hpp"
#include "Route.hpp"

class SFML_output
{
public:
	SFML_output();
	void display(Route& route);
	void clean();

	sf::RenderWindow& get_window();

private:
	sf::RenderWindow window;
};