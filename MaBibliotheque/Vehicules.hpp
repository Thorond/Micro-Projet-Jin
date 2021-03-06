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
	/* GETTERS AND SETTERS*/
	double get_x();
	void set_x( double x);
	double get_y();
	void set_y();
	double get_vitesse_x();
	void set_vitesse_x( double vitesse );
	void set_longueur( int longueur);
	double get_longueur();
	position_route get_position();
	void set_position( position_route position);
	etat_pare_choc get_etat_pc_avant();
	void set_etat_pc_avant(etat_pare_choc etat);
	etat_pare_choc get_etat_pc_arriere();
	void set_etat_pc_arriere(etat_pare_choc etat);


	virtual void construction_pare_choc(niveau niveau) = 0;
	virtual void choix_vitesse(niveau niveau) = 0; /* Choix de la vitesse du vehicule en fonction du niveau actuel*/
	virtual void adapter_sa_vitesse(Vehicules& vehiDevant); /* Permet d'adapter la vitesse d'un vehicule si celui devant
															va plus lentement que lui */

	Entitee corps;
	bool Update(); /* Synchronise les donnes porpres de la classe avec celles du corps de box2d*/
	void draw_circle(double x,double y , double r, sf::RenderWindow& window); 
	void draw_rectangle(double x, double y, double dx, double dy, sf::RenderWindow& window);
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void draw_corps(sf::RenderWindow& window) = 0;
	virtual void draw_pare_choc(sf::RenderWindow& window) = 0;

private:
	double x;
	double y;
	double vitesse_x;
	int longueur;
	position_route position_y;
	etat_pare_choc etat_pc_avant;
	etat_pare_choc etat_pc_arriere;

};