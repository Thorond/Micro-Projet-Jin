#include "Joueur.hpp"


Joueur::Joueur(double x, position_route position, double vitesse, niveau niveau, b2World* world)
	: Voitures(x, position, niveau, world)
{
	this->set_vitesse_x(vitesse);
	this->corps.body->SetLinearVelocity(b2Vec2(get_vitesse_x(), 0));
}

void Joueur::adapter_sa_vitesse(Vehicules& vehiDevant) {

}