
#include <iostream>
#include "Vehicules.hpp"


Vehicules::Vehicules(double x, double vitesse/*, position_route position*/, b2World* world)
	: x(x)
	, vitesse_x(vitesse)
	/*, position_y(position)*/
	, etat_pc_avant(indefini)
	, etat_pc_arriere(indefini)
	, corps(*world)
{
	corps.charger(this->x, 0);
}

//Vehicules::~Vehicules() {

//}


double Vehicules::get_x() { return x; }
void Vehicules::set_x(double x) {
	this->x = x;
}

double Vehicules::get_vitesse_x() { return vitesse_x; }
void Vehicules::set_vitesse_x(double vitesse) {
	this->vitesse_x = vitesse;
}

//position_route Vehicules::get_position() { return position_y; }
//void Vehicules::set_position(position_route position) {
//	this->position_y = position;
//}

etat_pare_choc Vehicules::get_etat_pc_avant() { return etat_pc_avant;  }
void Vehicules::set_etat_pc_avant(etat_pare_choc etat) {
	this->etat_pc_avant = etat;
}

etat_pare_choc Vehicules::get_etat_pc_arriere() { return etat_pc_arriere; }
void Vehicules::set_etat_pc_arriere(etat_pare_choc etat) {
	this->etat_pc_arriere = etat;
}


bool Vehicules::Update(/*sf::RenderWindow* window*/) {
	b2Vec2 pos = this->corps.body->GetPosition();
	//float32 rot = this->body->GetAngle();
	this->set_x(pos.x);
	return true;
}