#include "Camions.hpp"

Camions::Camions(double x, position_route position, niveau niveau, b2World* world)
	: Vehicules(x, position, world)
{
	this->construction_pare_choc(niveau);
	this->choix_vitesse(niveau);
	this->set_longueur(LONGUEUR_VOITURE * 2);
	corps.charger(x, this->get_y(), this->get_vitesse_x(), true);
}

void Camions::construction_pare_choc(niveau niveau) {
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

void Camions::choix_vitesse(niveau niveau) {

	std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<> pourcentage(0, 100);
	const int choix_vitesse = pourcentage(engine);

	if (niveau == un) {
		if (choix_vitesse < 75) {
			this->set_vitesse_x(VITESSE_DE_BASE -1);
		}
		else if (choix_vitesse < 95) {
			this->set_vitesse_x(VITESSE_DE_BASE -3);
		}
		else {
			this->set_vitesse_x(VITESSE_DE_BASE - 5);
		}
	}
	else if (niveau == deux) {
		if (choix_vitesse < 65) {
			this->set_vitesse_x(VITESSE_DE_BASE - 1);
		}
		else if (choix_vitesse < 90) {
			this->set_vitesse_x(VITESSE_DE_BASE - 3);
		}
		else {
			this->set_vitesse_x(VITESSE_DE_BASE - 5);
		}
	}
	else {
		if (choix_vitesse < 55) {
			this->set_vitesse_x(VITESSE_DE_BASE - 1);
		}
		else if (choix_vitesse < 80) {
			this->set_vitesse_x(VITESSE_DE_BASE - 3);
		}
		else {
			this->set_vitesse_x(VITESSE_DE_BASE - 5);
		}
	}
	this->set_vitesse_x(this->get_vitesse_x() - VITESSE_DEFILEMENT); // adapter la vitesse des IA avec le joueur 
}


void Camions::draw(sf::RenderWindow& window) {
	draw_corps(window);
	draw_pare_choc(window);
}

void Camions::draw_corps(sf::RenderWindow& window) {
	this->draw_circle(this->get_x() - LONGUEUR_VOITURE / 2 - 2 * RAYON_ROUE, this->get_y(), RAYON_ROUE, window);
	this->draw_circle(this->get_x() - LONGUEUR_VOITURE / 2 + 2 * RAYON_ROUE, this->get_y(), RAYON_ROUE, window);
	this->draw_circle(this->get_x() + LONGUEUR_VOITURE / 2 + 2 * RAYON_ROUE, this->get_y(), RAYON_ROUE, window);
	this->draw_circle(this->get_x() + LONGUEUR_VOITURE / 2 - 2 * RAYON_ROUE, this->get_y(), RAYON_ROUE, window);
	this->draw_rectangle(this->get_x() - LONGUEUR_VOITURE, this->get_y() - LARGEUR_VOITURE - RAYON_ROUE,
		LONGUEUR_VOITURE * 2, LARGEUR_VOITURE, window);
	this->draw_rectangle(this->get_x() + LONGUEUR_VOITURE / 2, this->get_y() - LARGEUR_VOITURE - RAYON_ROUE,
		LONGUEUR_VOITURE / 2, LARGEUR_VOITURE, window);
}
void Camions::draw_pare_choc(sf::RenderWindow& window) {
	if (get_etat_pc_arriere() == 1) {
		draw_rectangle(this->get_x() - LONGUEUR_VOITURE - 7, this->get_y() - 2 * RAYON_ROUE,
			1, RAYON_ROUE * 2, window);
	}
	else if (get_etat_pc_arriere() == 2) {
		draw_rectangle(this->get_x() - LONGUEUR_VOITURE - 7, this->get_y() - 2 * RAYON_ROUE,
			3, RAYON_ROUE * 2, window);
	}
	else if (get_etat_pc_arriere() == 3) {
		draw_rectangle(this->get_x() - LONGUEUR_VOITURE - 9, this->get_y() - 2 * RAYON_ROUE,
			5, RAYON_ROUE * 2, window);
	}

	if (get_etat_pc_avant() == 1) {
		draw_rectangle(this->get_x() + LONGUEUR_VOITURE + 5, this->get_y() - 2 * RAYON_ROUE,
			1, RAYON_ROUE * 2, window);
	}
	else if (get_etat_pc_avant() == 2) {
		draw_rectangle(this->get_x() + LONGUEUR_VOITURE + 5, this->get_y() - 2 * RAYON_ROUE,
			3, RAYON_ROUE * 2, window);
	}
	else if (get_etat_pc_avant() == 3) {
		draw_rectangle(this->get_x() + LONGUEUR_VOITURE + 5, this->get_y() - 2 * RAYON_ROUE,
			5, RAYON_ROUE * 2, window);
	}
}
