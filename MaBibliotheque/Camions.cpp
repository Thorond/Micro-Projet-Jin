#include "Camions.hpp"

Camions::Camions(double x, position_route position, niveau niveau, b2World* world)
	: Vehicules(x, position, world)
{
	this->construction_pare_choc(niveau);
	this->choix_vitesse(niveau);
	corps.charger(x, 0, this->get_vitesse_x(), true);
}

void Camions::construction_pare_choc(niveau niveau) {
	if (niveau == un) {
		this->set_etat_pc_avant(bon);
		this->set_etat_pc_arriere(bon);
	}
	else if (niveau == deux) {
		this->set_etat_pc_avant(excellent);
		this->set_etat_pc_arriere(excellent);
	}
	else {
		this->set_etat_pc_avant(indestructible);
		this->set_etat_pc_arriere(indestructible);
	}
}

void Camions::choix_vitesse(niveau niveau) {

	std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<> pourcentage(0, 100);
	const int choix_vitesse = pourcentage(engine);

	if (niveau == un) {
		if (choix_vitesse < 75) {
			this->set_vitesse_x(0.75f * VITESSE_DE_BASE);
		}
		else if (choix_vitesse < 95) {
			this->set_vitesse_x(0.50f * VITESSE_DE_BASE);
		}
		else {
			this->set_vitesse_x(0.25f * VITESSE_DE_BASE);
		}
	}
	else if (niveau == deux) {
		if (choix_vitesse < 65) {
			this->set_vitesse_x(0.75f * VITESSE_DE_BASE);
		}
		else if (choix_vitesse < 90) {
			this->set_vitesse_x(0.50f * VITESSE_DE_BASE);
		}
		else {
			this->set_vitesse_x(0.25f * VITESSE_DE_BASE);
		}
	}
	else {
		if (choix_vitesse < 55) {
			this->set_vitesse_x(0.75f * VITESSE_DE_BASE);
		}
		else if (choix_vitesse < 80) {
			this->set_vitesse_x(0.50f * VITESSE_DE_BASE);
		}
		else {
			this->set_vitesse_x(0.25f * VITESSE_DE_BASE);
		}
	}
	this->set_vitesse_x(this->get_vitesse_x() - VITESSE_DEFILEMENT); // adapter la vitesse des IA avec le joueur 
}


void Camions::draw(sf::RenderWindow& window) {
	this->draw_circle(this->get_x(), 4, window);
	this->draw_circle(this->get_x() + 10, 4, window);
	this->draw_circle(this->get_x() + 20, 4, window);
	this->draw_circle(this->get_x() + 30, 4, window);
	
}