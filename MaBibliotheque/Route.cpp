#include "Route.hpp"

Route::Route()
	: niveau_route(un)
	, etat_en_cours(en_jeu)
	, distance_parcouru(0)
{
	this->world = new b2World(b2Vec2(0, 0));
	auto voiture_joueur = std::make_unique<Joueur>(WINDOW_WIDTH / 2, milieu, 0, this->niveau_route, this->world);
	this->voie_milieu.push_back(std::move(voiture_joueur));
	this->index_voiture_joueur = 0;
	this->position_voiture_joueur = milieu;
}

/* GETTERS AND SETTERS */

etat_du_jeu Route::get_etat() { return etat_en_cours; }
void Route::set_etat(etat_du_jeu nouvEtat) { etat_en_cours = nouvEtat;  }

int Route::get_distance_parcouru() { return distance_parcouru; }
void Route::set_distance_parcouru(int dist) { distance_parcouru = dist; }

niveau Route::get_niveau() { return this->niveau_route; }
void Route::set_niveau(niveau nouvNiv) {
	this->niveau_route = nouvNiv;
}

b2World* Route::get_world() { return world; }

int Route::get_index_voiture_joueur() { return index_voiture_joueur; }
void Route::set_index_voiture_joueur(int index) { index_voiture_joueur = index; }
position_route Route::get_position_voiture_joueur() { return position_voiture_joueur; }
void Route::set_position_voiture_joueur(position_route pos) { position_voiture_joueur = pos; }

std::vector<std::unique_ptr<Vehicules>>& Route::get_voie_voiture(position_route pos) {
	if (pos == haute) return this->get_voie_haute();
	else if (pos == milieu) return this->get_voie_milieu();
	else return this->get_voie_basse();
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
Vehicules* Route::get_vehicule(position_route pos, int rang) {
	if (pos == haute) return voie_haute[rang].get();
	else if (pos == milieu) return voie_milieu[rang].get();
	else return voie_basse[rang].get();
}

/* FUNCTION MANAGING THE GAME*/

void Route::gestion_global(sf::Clock& clock, sf::Time& elapsed, sf::RenderWindow& window) {
	
	switch (etat_en_cours)
	{
	case en_jeu:
	{
		this->generation_automatique(clock, elapsed);
		this->Update(window);
		this->draw(window);
		break;
	}
	case pause :
		this->draw(window);
		break;
	case gameover :
		//destroy everithing
		break;
	default:
		break;
	}
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
				generation_vehicules(haute);
			}
			else if (choix_voie < FREQ * 2 / 3) {
				generation_vehicules(milieu);
			}
			else {
				generation_vehicules(basse);
			}
		}
		else {
			if (choix_voie < FREQ / 3) {
				generation_vehicules(haute);
				generation_vehicules(milieu);
			}
			else if (choix_voie < FREQ * 2 / 3) {
				generation_vehicules(milieu);
				generation_vehicules(basse);
			}
			else {
				generation_vehicules(basse);
				generation_vehicules(haute);
			}
		}
		elapsed = clock.restart();
	}
}

// fonction qui va générer les différents véhicules sur les différentes voies de la route
void Route::generation_vehicules( position_route posi) {
	std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<> pourcentage(0, 100);
	const int choix_voiture_camion = pourcentage(engine);

	std::vector<std::unique_ptr<Vehicules>>* voie;
	if (posi == haute) voie = &voie_haute;
	else if (posi == milieu) voie = &voie_milieu;
	else voie = &voie_basse;
	if (niveau_route == un ) {
		if (choix_voiture_camion < 80) {
			auto vehicule = std::make_unique<Voitures>(WINDOW_WIDTH + 100 , posi, this->get_niveau(),world );
			voie->push_back(std::move(vehicule));
		}
		else {
			auto vehicule = std::make_unique<Camions>(WINDOW_WIDTH + 100, posi , this->get_niveau(), world);
			voie->push_back(std::move(vehicule));
		}
	}
	else if (niveau_route == deux) {
		if (choix_voiture_camion < 70) {
			auto vehicule = std::make_unique<Voitures>(WINDOW_WIDTH + 100, posi, this->get_niveau(), world);
			voie->push_back(std::move(vehicule));
		}
		else {
			auto vehicule = std::make_unique<Camions>(WINDOW_WIDTH + 100, posi, this->get_niveau(), world);
			voie->push_back(std::move(vehicule));
		}
	}
	else {
		if (choix_voiture_camion < 60) {
			auto vehicule = std::make_unique<Voitures>(WINDOW_WIDTH + 100, posi, this->get_niveau(), world);
			voie->push_back(std::move(vehicule));
		}
		else {
			auto vehicule = std::make_unique<Camions>(WINDOW_WIDTH + 100, posi, this->get_niveau(), world);
			voie->push_back(std::move(vehicule));
		}
	}
	
	
}

bool Route::changer_de_voie(position_route choix, position_route posActuel, Vehicules& vehic, bool is_joueur  ) {
	assert((choix == haute && posActuel == milieu) || (choix == milieu && posActuel == basse)
		|| (choix == milieu && posActuel == haute) || (choix == basse && posActuel == milieu));
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
	size_t positionnement = 0;
	for (size_t i = 0; i < voie_de_changement->size(); i++) {
		if (get_vehicule(*voie_de_changement, i)->get_x() < vehic.get_x())
			positionnement++;
		else if (get_vehicule(*voie_de_changement, i)->get_x() > vehic.get_x()) {
			break;
		}
		else return false; 
	}
	if (positionnement >= 1) {
		if ( get_vehicule(*voie_de_changement, positionnement - 1)->get_x() > vehic.get_x() - 1.4* get_vehicule(*voie_de_changement, positionnement - 1)->get_longueur() ) return false;
	}
	else if (voie_de_changement->size() > (size_t)positionnement ) {
		if ( get_vehicule(*voie_de_changement, positionnement)->get_x() < vehic.get_x() + 1.7*  get_vehicule(*voie_de_changement, positionnement )->get_longueur()) return false;
	}

	auto vehi = std::make_unique<Voitures>(vehic.get_x(), vehic.get_position(), vehic.get_vitesse_x(), this->get_niveau(), world);
	if (is_joueur) vehi = std::make_unique<Joueur>(vehic.get_x(), vehic.get_position(), vehic.get_vitesse_x(), this->get_niveau(), world);
	vehi.get()->set_etat_pc_arriere(vehic.get_etat_pc_arriere());
	vehi.get()->set_etat_pc_avant(vehic.get_etat_pc_avant());
	
	for (size_t i = 0; i < voie_actuel->size(); i++) {
		if (get_vehicule(*voie_actuel, i)->get_x() == vehi.get()->get_x()) {
			voie_actuel->erase(voie_actuel->begin() + i);
			if (posActuel == position_voiture_joueur && i < index_voiture_joueur ) index_voiture_joueur--;
			break;
		}
	}
	
	vehi.get()->set_position(choix);
	vehi.get()->set_y();
	if (is_joueur) {
		index_voiture_joueur = positionnement;
		position_voiture_joueur = choix;
	}
	else {
		if (choix == position_voiture_joueur && positionnement <= index_voiture_joueur) index_voiture_joueur++;
	}
	if (positionnement == voie_de_changement->size()) voie_de_changement->push_back(std::move(vehi));
	else voie_de_changement->insert(voie_de_changement->begin() + positionnement, std::move(vehi));
	
	
	return true;
}

bool Route::changer_de_voie_haut_joueur() {
	bool reussi;
	if (this->get_position_voiture_joueur() == milieu)
		reussi = this->changer_de_voie(haute, milieu,
			*this->get_vehicule(this->get_voie_milieu(),
				this->get_index_voiture_joueur()), true);
	else if (this->get_position_voiture_joueur() == basse)
		reussi = this->changer_de_voie(milieu, basse,
			*this->get_vehicule(this->get_voie_basse(),
				this->get_index_voiture_joueur()), true);
	else return false;
	return reussi;
}

bool Route::changer_de_voie_bas_joueur() {
	bool reussi;
	if (this->get_position_voiture_joueur() == milieu)
		reussi = this->changer_de_voie(basse, milieu,
			*this->get_vehicule(this->get_voie_milieu(),
				this->get_index_voiture_joueur()), true);
	else if (this->get_position_voiture_joueur() == haute)
		reussi = this->changer_de_voie(milieu, haute,
			*this->get_vehicule(this->get_voie_haute(),
				this->get_index_voiture_joueur()), true);
	else return false;
	return reussi;
}



void Route::Update(sf::RenderWindow& window) {
	this->world->Step(1.0f / 60.0f, 6, 2);
	gestion_voiture_joueur();
	distance_parcouru++;

	for (size_t i = 0; i < voie_haute.size(); i++) {
		if (this->get_vehicule(voie_haute, i)->get_x() < -100) {
			voie_haute.erase(voie_haute.begin() + i);
			if (haute == position_voiture_joueur && i < index_voiture_joueur) index_voiture_joueur--;
		}
	}
	for (size_t i = 0; i < voie_haute.size(); i++) {
		this->get_vehicule(voie_haute, i)->Update(window);
		if (i + 1 < voie_haute.size()) this->get_vehicule(voie_haute, i)->adapter_sa_vitesse(*(this->get_vehicule(voie_haute, i + 1)));
	}
	for (size_t i = 0; i < voie_milieu.size(); i++) {
		if (this->get_vehicule(voie_milieu, i)->get_x() < -100) {
			voie_milieu.erase(voie_milieu.begin() + i);
			if (milieu == position_voiture_joueur && i < index_voiture_joueur) index_voiture_joueur--;
		}
	}
	for (size_t i = 0; i < voie_milieu.size(); i++) {
		this->get_vehicule(voie_milieu, i)->Update(window);
		if (i + 1 < voie_milieu.size()) this->get_vehicule(voie_milieu, i)->adapter_sa_vitesse(*(this->get_vehicule(voie_milieu, i + 1)));
	}
	for (size_t i = 0; i < voie_basse.size(); i++) {
		if (this->get_vehicule(voie_basse, i)->get_x() < -100) {
			voie_basse.erase(voie_basse.begin() + i);
			if (basse == position_voiture_joueur && i < index_voiture_joueur) index_voiture_joueur--;
		}
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

void Route::gestion_voiture_joueur() {
	Joueur* voiture_joueur = (Joueur*) this->get_vehicule(this->get_position_voiture_joueur(), this->get_index_voiture_joueur());
	voiture_joueur->regulation_vitesse_bords();
	this->set_index_voiture_joueur(
		voiture_joueur->gestion_collision(this->get_voie_voiture(get_position_voiture_joueur()),
			get_index_voiture_joueur()));

	if (voiture_joueur->get_etat_pc_avant() < 0 || voiture_joueur->get_etat_pc_arriere() < 0) {
		this->etat_en_cours = gameover;
	}
}