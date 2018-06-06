#include "Joueur.hpp"


Joueur::Joueur(double x, position_route position, double vitesse, niveau niveau, b2World* world)
	: Voitures(x, position, niveau, world)
{
	this->set_vitesse_x(vitesse);
	this->corps.body->SetLinearVelocity(b2Vec2(get_vitesse_x(), 0));
}

void Joueur::adapter_sa_vitesse(Vehicules& vehiDevant) {

}

void Joueur::regulation_vitesse_bords() {
	if (this->get_vitesse_x() > 0 
		&& this->get_x() + LONGUEUR_VOITURE > WINDOW_WIDTH) this->set_vitesse_x(VITESSE_DEFILEMENT - VITESSE_DEFILEMENT);
	else if (this->get_vitesse_x() < 0 
		&& this->get_x() - LONGUEUR_VOITURE < 0 ) this->set_vitesse_x(VITESSE_DEFILEMENT - VITESSE_DEFILEMENT);
}