#pragma once
#include "Voitures.hpp"
#include "Camions.hpp"
#include <vector>
#include <memory>
#include <random>
#include <SFML/Graphics.hpp>



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

	//void generation_automatique(); // générer pour les trois voies une voiture ou un camion de
								// façon assez régulière
	void generation_vehicules(std::vector<std::unique_ptr<Vehicules>>& voie);
	void consequence_collision(Vehicules& v1, Vehicules& v2);

	void Update(/*sf::RenderWindow* window */);

private :
	niveau niveau_route;
	std::vector<std::unique_ptr<Vehicules>> voie_haute;
	std::vector<std::unique_ptr<Vehicules>> voie_milieu;
	std::vector<std::unique_ptr<Vehicules>> voie_basse;

	b2World * world;
};