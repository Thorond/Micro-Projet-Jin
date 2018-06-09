#include "EventHandler.hpp"


void event_en_jeu(Route& route, sf::Event& event) {
	if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up) {
		route.changer_de_voie_haut_joueur();
	}
	else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
		route.changer_de_voie_bas_joueur();
	}
	else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
		Joueur* voiture_joueur = (Joueur*)route.get_vehicule(route.get_position_voiture_joueur(), route.get_index_voiture_joueur());
		if (voiture_joueur->get_vitesse_x() < VITESSE_MAX_RELATIVE
			&& voiture_joueur->get_x() + LONGUEUR_VOITURE < WINDOW_WIDTH) {
			voiture_joueur->set_vitesse_x(voiture_joueur->get_vitesse_x() + 1);
		}
	}
	else if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Left) {
		Joueur* voiture_joueur = (Joueur*)route.get_vehicule(route.get_position_voiture_joueur(), route.get_index_voiture_joueur());
		if (voiture_joueur->get_vitesse_x() > VITESSE_MIN_RELATIVE
			&& voiture_joueur->get_x() - LONGUEUR_VOITURE > 0) {
			voiture_joueur->set_vitesse_x(voiture_joueur->get_vitesse_x() - 2);
		}
	}

	else if (event.key.code == sf::Keyboard::P) {
		route.set_etat(pause);
	}
}

void event_pause(Route& route, sf::Event& event) {
	if (event.key.code == sf::Keyboard::P) {
		route.set_etat(en_jeu);
	}
}

void event_game_over(Route& route, sf::Event& event) {
	if (event.key.code == sf::Keyboard::Return) {
		route.set_etat(en_jeu);
		Joueur* voiture_joueur = (Joueur*)route.get_vehicule(route.get_position_voiture_joueur(), route.get_index_voiture_joueur());
		voiture_joueur->set_etat_pc_arriere(abime);
		voiture_joueur->set_etat_pc_avant(abime);
	}
}