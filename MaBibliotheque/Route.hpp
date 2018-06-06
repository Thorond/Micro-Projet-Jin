#pragma once
#include "Joueur.hpp"
#include "Camions.hpp"
#include <vector>
#include <memory>
#include <random>
#include <iostream>


class Route 
{
public :
	Route();
	niveau get_niveau();
	void set_niveau(niveau nouvNiv);

	b2World* get_world();

	int get_index_voiture_joueur();
	void set_index_voiture_joueur(int index);
	position_route get_position_voiture_joueur();
	void set_position_voiture_joueur(position_route pos);

	std::vector<std::unique_ptr<Vehicules>>& get_voie_haute();
	std::vector<std::unique_ptr<Vehicules>>& get_voie_milieu();
	std::vector<std::unique_ptr<Vehicules>>& get_voie_basse();
	
	Vehicules* get_vehicule(std::vector<std::unique_ptr<Vehicules>>& voie, int rang);
	Vehicules* get_vehicule(position_route pos, int rang);
	
	void gestion_global(sf::Clock& clock, sf::Time& elapsed, sf::RenderWindow& window);
	void generation_automatique(sf::Clock& clock , sf::Time& elapsed); // g�n�rer pour les trois voies une voiture ou un camion de
								// fa�on assez r�guli�re
	void generation_vehicules( position_route posi);

	bool changer_de_voie(position_route choix, position_route posActuel, Vehicules& vehic, bool is_joueur);
	bool changer_de_voie_haut_joueur();
	bool changer_de_voie_bas_joueur();
	void consequence_collision(Vehicules& v1, Vehicules& v2);

	void Update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);


private :
	niveau niveau_route;
	std::vector<std::unique_ptr<Vehicules>> voie_haute;
	std::vector<std::unique_ptr<Vehicules>> voie_milieu;
	std::vector<std::unique_ptr<Vehicules>> voie_basse;

	b2World * world;

	int index_voiture_joueur;
	position_route position_voiture_joueur;
};