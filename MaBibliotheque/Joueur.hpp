#pragma once
#include "Voitures.hpp"

class Joueur : public Voitures
{
public :
	Joueur(double x, position_route position, double vitesse , niveau niveau, b2World* world);
	void adapter_sa_vitesse(Vehicules& vehiDevant) override;
	void draw_corps(sf::RenderWindow& window) override;
	void regulation_vitesse_bords();

	int unsigned gestion_collision(std::vector<std::unique_ptr<Vehicules>>& voie_joueur, int unsigned index_voiture);

private :
};