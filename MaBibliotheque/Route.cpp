#include "Route.hpp"

Route::Route()
	: niveau_route(un)
{
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

// fonction qui va g�n�rer les diff�rents v�hicules sur les diff�rentes voies de la route
void Route::generation_vehicules(std::vector<std::unique_ptr<Vehicules>>& voie) {
	
	auto vehicule = std::make_unique<Voitures>(500, 70, this->get_niveau());
	voie.push_back(std::move(vehicule));
	
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