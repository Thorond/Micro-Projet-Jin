#pragma once
#include "Voitures.hpp"
#include <vector>
#include <memory>



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

	void generation_vehicules(std::vector<std::unique_ptr<Vehicules>>& voie);

private :
	niveau niveau_route;
	std::vector<std::unique_ptr<Vehicules>> voie_haute;
	std::vector<std::unique_ptr<Vehicules>> voie_milieu;
	std::vector<std::unique_ptr<Vehicules>> voie_basse;
};