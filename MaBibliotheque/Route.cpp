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

// fonction qui va générer les différents véhicules sur les différentes voies de la route
void Route::generation_vehicules(std::vector<std::unique_ptr<Vehicules>>& voie) {
	if (voie.size() == 0) {
		auto vehicule = std::make_unique<Voitures>(500, 70, this->get_niveau());
		voie.push_back(std::move(vehicule));
	}
}