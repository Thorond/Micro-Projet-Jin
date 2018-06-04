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
	std::vector<std::unique_ptr<Vehicules>>& get_voie_haute();
	std::vector<std::unique_ptr<Vehicules>>& get_voie_milieu();
	std::vector<std::unique_ptr<Vehicules>>& get_voie_basse();
	
	Vehicules* get_vehicule(std::vector<std::unique_ptr<Vehicules>>& voie, int rang);

	void generation_automatique(sf::Clock& clock , sf::Time& elapsed); // générer pour les trois voies une voiture ou un camion de
								// façon assez régulière
	void generation_vehicules(std::vector<std::unique_ptr<Vehicules>>& voie, position_route posi);

	bool changer_de_voie(position_route choix, position_route posActuel, Vehicules& vehic, bool is_joueur);
	void consequence_collision(Vehicules& v1, Vehicules& v2);

	void Update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	int get_index_voiture_joueur();
	void set_index_voiture_joueur(int index);
	position_route get_position_voiture_joueur();
	void set_position_voiture_joueur(position_route pos);

private :
	niveau niveau_route;
	std::vector<std::unique_ptr<Vehicules>> voie_haute;
	std::vector<std::unique_ptr<Vehicules>> voie_milieu;
	std::vector<std::unique_ptr<Vehicules>> voie_basse;

	b2World * world;

	int index_voiture_joueur;
	position_route position_voiture_joueur;
};