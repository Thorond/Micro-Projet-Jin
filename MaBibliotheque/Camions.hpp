#pragma once
#include "Vehicules.hpp"

class Camions : public Vehicules
{

public:
	Camions(double x, position_route position, niveau niveau, b2World* world);
	void construction_pare_choc(niveau niveau) override;
	void choix_vitesse(niveau niveau) override;
	void draw(sf::RenderWindow& window) override;

}; 
