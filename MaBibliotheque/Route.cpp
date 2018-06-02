#include "Route.hpp"

Route::Route()
	: niveau_route(un)
{
	this->world = new b2World(b2Vec2(0, 0));
}

niveau Route::get_niveau() { return this->niveau_route; }
void Route::set_niveau(niveau nouvNiv) {
	this->niveau_route = nouvNiv;
}

std::vector<std::unique_ptr<Vehicules>>& Route::get_voie_haute() {
	return this->voie_haute;
}
std::vector<std::unique_ptr<Vehicules>>& Route::get_voie_milieu() {
	return this->voie_milieu;
}
std::vector<std::unique_ptr<Vehicules>>& Route::get_voie_basse() {
	return this->voie_basse;
}

Vehicules* Route::get_vehicule(std::vector<std::unique_ptr<Vehicules>>& voie, int rang) {
	return voie[rang].get();
}

void Route::generation_automatique() {
	generation_vehicules(voie_haute);
	generation_vehicules(voie_milieu);
	generation_vehicules(voie_basse);
}

// fonction qui va générer les différents véhicules sur les différentes voies de la route
void Route::generation_vehicules(std::vector<std::unique_ptr<Vehicules>>& voie) {
	std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<> pourcentage(0, 100);
	const int choix_voiture_camion = pourcentage(engine);

	if (niveau_route == un ) {
		if (choix_voiture_camion < 80) {
			auto vehicule = std::make_unique<Voitures>(500, this->get_niveau(),world);
			voie.push_back(std::move(vehicule));
		}
		else {
			auto vehicule = std::make_unique<Camions>(500, this->get_niveau(), world);
			voie.push_back(std::move(vehicule));
		}
	}
	else if (niveau_route == deux) {
		if (choix_voiture_camion < 70) {
			auto vehicule = std::make_unique<Voitures>(500, this->get_niveau(), world);
			voie.push_back(std::move(vehicule));
		}
		else {
			auto vehicule = std::make_unique<Camions>(500, this->get_niveau(), world);
			voie.push_back(std::move(vehicule));
		}
	}
	else {
		if (choix_voiture_camion < 60) {
			auto vehicule = std::make_unique<Voitures>(500, this->get_niveau(), world);
			voie.push_back(std::move(vehicule));
		}
		else {
			auto vehicule = std::make_unique<Camions>(500, this->get_niveau(), world);
			voie.push_back(std::move(vehicule));
		}
	}
	
	
}


void Route::consequence_collision(Vehicules& v1, Vehicules& v2) {
	int pcv1;
	int pcv2;
	if (v1.get_x() > v2.get_x()) {
		pcv1 = v1.get_etat_pc_arriere();
		pcv2 = v2.get_etat_pc_avant();
		v1.set_etat_pc_arriere((etat_pare_choc)(pcv1 - pcv2));
		v2.set_etat_pc_avant((etat_pare_choc)(pcv2 - pcv1));
		if (v1.get_etat_pc_arriere() <= 0) {
			// Faire disparaitre le vehicule
		}
		if (v2.get_etat_pc_avant() <= 0) {
			// Faire disparaitre le vehicule
		}
	}
	else {
		pcv1 = v1.get_etat_pc_avant();
		pcv2 = v2.get_etat_pc_arriere();
		v2.set_etat_pc_arriere((etat_pare_choc)(pcv2 - pcv1));
		v1.set_etat_pc_avant((etat_pare_choc)(pcv1 - pcv2));
		if (v2.get_etat_pc_arriere() <= 0) {
			// Faire disparaitre le vehicule
		}
		if (v1.get_etat_pc_avant() <= 0) {
			// Faire disparaitre le vehicule
		}
	}
}



void Route::Update(sf::RenderWindow& window) {
	this->world->Step(1.0f / 60.0f, 6, 2);
	for (size_t k = 0; k < this->voie_basse.size(); k++) {
		this->get_vehicule(voie_basse, k)->Update(window);
	}
}

void Route::draw(sf::RenderWindow& window) {
	for (size_t i = 0; i < voie_haute.size(); i++) {
		this->get_vehicule(voie_haute, i)->draw(window);
	}
	for (size_t i = 0; i < voie_milieu.size(); i++) {
		this->get_vehicule(voie_milieu, i)->draw(window);
	}
	for (size_t i = 0; i < voie_basse.size(); i++) {
		this->get_vehicule(voie_basse, i)->draw(window);
	}
}