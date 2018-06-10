#pragma once
#include "Route.hpp"
#include <SFML/Graphics.hpp>

void event_en_jeu(Route& route, sf::Event& event ); 
void event_pause(Route& route, sf::Event& event);
void event_game_over(Route& route, sf::Event& event);
void event_menu_demarrer(Route& route, sf::Event& event);


