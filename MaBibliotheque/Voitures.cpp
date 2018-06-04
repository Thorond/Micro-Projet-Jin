#include "Voitures.hpp"

Voitures::Voitures(double x, position_route position, niveau niveau, b2World* world)
	: Vehicules(x, position,world)
{
	this->construction_pare_choc(niveau);
	this->choix_vitesse(niveau);
	int y;
	if (position == haute) y = 85;
	else if (position == milieu) y = 50;
	else y = 15;
	corps.charger(x, y, this->get_vitesse_x(), false);
}

void Voitures::construction_pare_choc(niveau niveau) {
	if (niveau == un) {
		this->set_etat_pc_avant(abime);
		this->set_etat_pc_arriere(abime);
	}
	else if (niveau == deux) {
		this->set_etat_pc_avant(bon);
		this->set_etat_pc_arriere(bon);
	}
	else {
		this->set_etat_pc_avant(excellent);
		this->set_etat_pc_arriere(excellent);
	}
}

void Voitures::choix_vitesse(niveau niveau) {

	std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<> pourcentage(0, 100);
	const int choix_vitesse = pourcentage(engine);

	if (niveau == un) {
		if (choix_vitesse < 75) {
			this->set_vitesse_x(VITESSE_DE_BASE);
		}
		else if (choix_vitesse < 95) {
			this->set_vitesse_x(VITESSE_DE_BASE + 2);
		}
		else {
			this->set_vitesse_x(VITESSE_DE_BASE +4);
		}
	}
	else if (niveau == deux) {
		if (choix_vitesse < 65) {
			this->set_vitesse_x(VITESSE_DE_BASE);
		}
		else if (choix_vitesse < 90) {
			this->set_vitesse_x(VITESSE_DE_BASE + 2);
		}
		else {
			this->set_vitesse_x(VITESSE_DE_BASE + 4);
		}
	}
	else {
		if (choix_vitesse < 55) {
			this->set_vitesse_x(VITESSE_DE_BASE);
		}
		else if (choix_vitesse < 80) {
			this->set_vitesse_x(VITESSE_DE_BASE + 2);
		}
		else {
			this->set_vitesse_x(VITESSE_DE_BASE + 4);
		}
	}
	this->set_vitesse_x(this->get_vitesse_x() - VITESSE_DEFILEMENT); // adapter la vitesse des IA relativement au joueur 
}

void Voitures::draw(sf::RenderWindow& window) {
	this->draw_circle(this->get_x(), 4, window);
	this->draw_circle(this->get_x()+10, 4, window);
}