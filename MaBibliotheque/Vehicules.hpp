#pragma once
#include "EnumEtDonnees.hpp"
#include "Entitee.hpp"
#include <random>
#include <SFML\Graphics.hpp>

class Vehicules
{
public:
	Vehicules(double x, position_route position, b2World* world);
	~Vehicules();
	double get_x();
	void set_x( double x);
	double get_vitesse_x();
	void set_vitesse_x( double vitesse );
	position_route get_position();
	void set_position( position_route position);
	etat_pare_choc get_etat_pc_avant();
	void set_etat_pc_avant(etat_pare_choc etat);
	etat_pare_choc get_etat_pc_arriere();
	void set_etat_pc_arriere(etat_pare_choc etat);


	virtual void construction_pare_choc(niveau niveau) = 0;
	virtual void choix_vitesse(niveau niveau) = 0;
	virtual void adapter_sa_vitesse(Vehicules& vehiDevant);

	Entitee corps;
	bool Update(sf::RenderWindow& window);
	void draw_circle(double x, double r, sf::RenderWindow& window);
	virtual void draw(sf::RenderWindow& window) = 0;

private:
	double x;
	double vitesse_x;
	position_route position_y;
	etat_pare_choc etat_pc_avant;
	etat_pare_choc etat_pc_arriere;

};