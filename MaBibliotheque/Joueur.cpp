#include "Joueur.hpp"


Joueur::Joueur(double x, position_route position, double vitesse, niveau niveau, b2World* world)
	: Voitures(x, position, niveau, world)
{
	this->set_vitesse_x(vitesse);
	this->corps.body->SetLinearVelocity(b2Vec2((float32)get_vitesse_x(), 0));
	this->set_etat_pc_arriere(abime);
	this->set_etat_pc_avant(abime);
}

void Joueur::adapter_sa_vitesse(Vehicules& vehiDevant) {

}
void Joueur::draw_corps(sf::RenderWindow& window) {
	this->draw_circle(this->get_x() - LONGUEUR_VOITURE / 3, this->get_y(), RAYON_ROUE, window);
	this->draw_circle(this->get_x() + LONGUEUR_VOITURE / 3, this->get_y(), RAYON_ROUE, window);
	this->draw_rectangle(this->get_x() - LONGUEUR_VOITURE / 2, this->get_y() - LARGEUR_VOITURE/2 - RAYON_ROUE,
		LONGUEUR_VOITURE, LARGEUR_VOITURE/2, window);
	this->draw_rectangle(this->get_x(), this->get_y() - LARGEUR_VOITURE/2 - RAYON_ROUE,
		LONGUEUR_VOITURE / 2, LARGEUR_VOITURE / 2, window);
}

/* Cette fonction permet d'empecher le joueur de sortir des limites de la fenetre*/
void Joueur::regulation_vitesse_bords() {
	if (this->get_vitesse_x() > 0 
		&& this->get_x() + LONGUEUR_VOITURE > WINDOW_WIDTH) this->set_vitesse_x(VITESSE_DEFILEMENT - VITESSE_DEFILEMENT);
	else if (this->get_vitesse_x() < 0 
		&& this->get_x() - LONGUEUR_VOITURE < 0 ) this->set_vitesse_x(VITESSE_DEFILEMENT - VITESSE_DEFILEMENT);
}

/* Fonction permettant de gerer lorsque le vehicule du joueur est trop proche d'un autre vehicule ainsi que
les consequences associees.*/
int unsigned Joueur::gestion_collision(std::vector<std::unique_ptr<Vehicules>>& voie_joueur, int unsigned index_voiture ) {
	if (index_voiture + 1 < voie_joueur.size()) {
		Vehicules* vehicule_face = voie_joueur[index_voiture + 1].get();
		if (vehicule_face->get_x() - 1.7 * vehicule_face->get_longueur() < this->get_x()) {
			this->corps.body->SetTransform(b2Vec2((float32)(vehicule_face->get_x() - 2 * vehicule_face->get_longueur()),0),0);
			this->set_vitesse_x(vehicule_face->get_vitesse_x());
			index_voiture = this->consequence_collision(voie_joueur, index_voiture, *vehicule_face);
		}
	}

	if (index_voiture >= 1 ) {
		Vehicules* vehicule_arri�re = voie_joueur[index_voiture -1].get();
		if (vehicule_arri�re->get_x() + 1.4 * vehicule_arri�re->get_longueur() > this->get_x()) {
			this->corps.body->SetTransform(b2Vec2((float32)(vehicule_arri�re->get_x() + 2 * vehicule_arri�re->get_longueur()), 0), 0);
			this->set_vitesse_x(vehicule_arri�re->get_vitesse_x());
			index_voiture = this->consequence_collision(voie_joueur, index_voiture, *vehicule_arri�re);
		}
	}

	return index_voiture;
}