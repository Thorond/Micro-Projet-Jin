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

void Route::generation_automatique(sf::Clock& clock, sf::Time& elapsed) {
	const unsigned int FREQ(1800);
	std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<> distri_generation(0, FREQ);
	const int nombre_voie = distri_generation(engine);
	const int choix_voie = distri_generation(engine);

	if (elapsed.asSeconds() > 3 ) { // generation toutes les trois secondes
		if (nombre_voie < FREQ / 2) {
			if (choix_voie < FREQ / 3) {
				generation_vehicules(voie_haute, haute);
			}
			else if (choix_voie < FREQ * 2 / 3) {
				generation_vehicules(voie_milieu, milieu);
			}
			else {
				generation_vehicules(voie_basse, basse);
			}
		}
		else {
			if (choix_voie < FREQ / 3) {
				generation_vehicules(voie_haute, haute);
				generation_vehicules(voie_milieu, milieu);
			}
			else if (choix_voie < FREQ * 2 / 3) {
				generation_vehicules(voie_milieu, milieu);
				generation_vehicules(voie_basse, basse);
			}
			else {
				generation_vehicules(voie_basse, basse);
				generation_vehicules(voie_haute, haute);
			}
		}
		elapsed = clock.restart();
	}
}

// fonction qui va g�n�rer les diff�rents v�hicules sur les diff�rentes voies de la route
void Route::generation_vehicules(std::vector<std::unique_ptr<Vehicules>>& voie, position_route posi) {
	std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<> pourcentage(0, 100);
	const int choix_voiture_camion = pourcentage(engine);

	if (niveau_route == un ) {
		if (choix_voiture_camion < 80) {
			auto vehicule = std::make_unique<Voitures>(WINDOW_WIDTH + 100 , posi, this->get_niveau(),world );
			voie.push_back(std::move(vehicule));
		}
		else {
			auto vehicule = std::make_unique<Camions>(WINDOW_WIDTH + 100, posi , this->get_niveau(), world);
			voie.push_back(std::move(vehicule));
		}
	}
	else if (niveau_route == deux) {
		if (choix_voiture_camion < 70) {
			auto vehicule = std::make_unique<Voitures>(WINDOW_WIDTH + 100, posi, this->get_niveau(), world);
			voie.push_back(std::move(vehicule));
		}
		else {
			auto vehicule = std::make_unique<Camions>(WINDOW_WIDTH + 100, posi, this->get_niveau(), world);
			voie.push_back(std::move(vehicule));
		}
	}
	else {
		if (choix_voiture_camion < 60) {
			auto vehicule = std::make_unique<Voitures>(WINDOW_WIDTH + 100, posi, this->get_niveau(), world);
			voie.push_back(std::move(vehicule));
		}
		else {
			auto vehicule = std::make_unique<Camions>(WINDOW_WIDTH + 100, posi, this->get_niveau(), world);
			voie.push_back(std::move(vehicule));
		}
	}
	
	
}

bool Route::changer_de_voie(position_route choix, position_route posActuel, Vehicules& vehic ) {
	assert((choix == haute && posActuel == milieu) || (choix == milieu && posActuel == basse)
		|| (choix == milieu && posActuel == haute) || (choix == basse && posActuel == milieu));
	auto vehi = std::make_unique<Voitures>(vehic.get_x(), vehic.get_position(), this->get_niveau(), world ); // que voitures
	std::vector<std::unique_ptr<Vehicules>>* voie_de_changement;
	std::vector<std::unique_ptr<Vehicules>>* voie_actuel;
	if (choix == haute && posActuel == milieu) {
		voie_de_changement = &get_voie_haute();
		voie_actuel = &get_voie_milieu();
	}
	else if ((choix == milieu && posActuel == basse)) {
		voie_de_changement = &get_voie_milieu();
		voie_actuel = &get_voie_basse();
	}
	else if ((choix == milieu && posActuel == haute)) {
		voie_de_changement = &get_voie_milieu();
		voie_actuel = &get_voie_haute();
	}
	else {
		voie_de_changement = &get_voie_basse();
		voie_actuel = &get_voie_milieu();
	}
	int positionnement = 0;
	for (size_t i = 0; i < voie_actuel->size(); i++) {
		if (get_vehicule(*voie_actuel, i)->get_x() == vehi.get()->get_x()) {
			voie_actuel->erase(voie_actuel->begin() + i);
			break;
		}
	}
	for (size_t i = 0; i < voie_de_changement->size(); i++) {
		if (get_vehicule(*voie_de_changement, i)->get_x() < vehi.get()->get_x())
			positionnement++;
		else if (get_vehicule(*voie_de_changement, i)->get_x() > vehi.get()->get_x()) {
			voie_de_changement->insert(voie_de_changement->begin() + i, std::move(vehi));
			break;
		}
		else return false;
	}
	if (positionnement == voie_de_changement->size()) voie_de_changement->push_back(std::move(vehi));
	
	return true;
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
	for (size_t i = 0; i < voie_haute.size(); i++) { // est ce que l'on supprime r�element l'objet?
		if (this->get_vehicule(voie_haute, i)->get_x() < - 100) voie_haute.erase(voie_haute.begin() + i);
	}
	for (size_t i = 0; i < voie_haute.size(); i++) {
		this->get_vehicule(voie_haute, i)->Update(window);
		if (i + 1 < voie_haute.size()) this->get_vehicule(voie_haute, i)->adapter_sa_vitesse(*(this->get_vehicule(voie_haute, i + 1)));
	}
	for (size_t i = 0; i < voie_milieu.size(); i++) {
		if (this->get_vehicule(voie_milieu, i)->get_x() < -100) voie_milieu.erase(voie_milieu.begin() + i);
	}
	for (size_t i = 0; i < voie_milieu.size(); i++) {
		this->get_vehicule(voie_milieu, i)->Update(window);
		if (i + 1 < voie_milieu.size()) this->get_vehicule(voie_milieu, i)->adapter_sa_vitesse(*(this->get_vehicule(voie_milieu, i + 1)));
	}
	for (size_t i = 0; i < voie_basse.size(); i++) {
		if (this->get_vehicule(voie_basse, i)->get_x() < -100) voie_basse.erase(voie_basse.begin() + i);
	}
	for (size_t i = 0; i < this->voie_basse.size(); i++) {
		this->get_vehicule(voie_basse, i)->Update(window);
		if (i + 1 < voie_basse.size()) this->get_vehicule(voie_basse, i)->adapter_sa_vitesse(*(this->get_vehicule(voie_basse, i + 1)));
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