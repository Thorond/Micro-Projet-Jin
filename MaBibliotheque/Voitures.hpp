#pragma once
#include "Vehicules.hpp"

class Voitures : public Vehicules
{

public :
	Voitures(double x, position_route position, niveau niveau, b2World* world);
	Voitures(double x, position_route position, double vitesse, niveau niveau, b2World* world);
	void construction_pare_choc(niveau niveau) override;
	void choix_vitesse(niveau niveau) override;
	void draw(sf::RenderWindow& window) override;

};