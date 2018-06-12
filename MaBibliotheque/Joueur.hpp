#pragma once
#include "Voitures.hpp"

class Joueur : public Voitures
{
public :
	Joueur(double x, position_route position, double vitesse , niveau niveau, b2World* world);
	void adapter_sa_vitesse(Vehicules& vehiDevant) override; // fonction rendu vide puisqu'on ne veut pas d'AI ici
	void draw_corps(sf::RenderWindow& window) override;
	void regulation_vitesse_bords();/* Cette fonction permet d'empecher le joueur de sortir des limites de la fenetre*/

	/* Fonction permettant de gerer lorsque le vehicule du joueur est trop proche d'un autre vehicule ainsi que 
	les consequences associees.*/
	int unsigned gestion_collision(std::vector<std::unique_ptr<Vehicules>>& voie_joueur, int unsigned index_voiture);

private :
};