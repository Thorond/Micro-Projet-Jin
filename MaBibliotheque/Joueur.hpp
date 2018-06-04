#pragma once
#include "Voitures.hpp"

class Joueur : public Voitures
{
public :
	Joueur(double x, position_route position, double vitesse , niveau niveau, b2World* world);
	void adapter_sa_vitesse(Vehicules& vehiDevant) override;
private :
};