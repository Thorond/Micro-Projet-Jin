
#include <iostream>
#include "Vehicules.hpp"


Vehicules::Vehicules(double x, position_route position, b2World* world)
	: x(x)
	, vitesse_x(0)
	, position_y(position)
	, etat_pc_avant(indefini)
	, etat_pc_arriere(indefini)
	, corps(*world)
{
	
}

Vehicules::~Vehicules() {

}


double Vehicules::get_x() { return x; }
void Vehicules::set_x(double x) {
	this->x = x;
}

double Vehicules::get_vitesse_x() { return vitesse_x; }
void Vehicules::set_vitesse_x(double vitesse) {
	this->vitesse_x = vitesse;
}

position_route Vehicules::get_position() { return position_y; }
void Vehicules::set_position(position_route position) {
	this->position_y = position;
}

etat_pare_choc Vehicules::get_etat_pc_avant() { return etat_pc_avant;  }
void Vehicules::set_etat_pc_avant(etat_pare_choc etat) {
	this->etat_pc_avant = etat;
}

etat_pare_choc Vehicules::get_etat_pc_arriere() { return etat_pc_arriere; }
void Vehicules::set_etat_pc_arriere(etat_pare_choc etat) {
	this->etat_pc_arriere = etat;
}

void Vehicules::adapter_sa_vitesse(Vehicules& vehiDevant) {
	if (vehiDevant.get_x() - this->get_x() < 1000 && vehiDevant.get_vitesse_x() < this->get_vitesse_x() ) {
		this->set_vitesse_x(vehiDevant.get_vitesse_x() );
		this->corps.body->SetLinearVelocity(b2Vec2(vehiDevant.get_vitesse_x(), 0));
	}
}


bool Vehicules::Update(sf::RenderWindow& window) {
	b2Vec2 pos = this->corps.body->GetPosition();
	this->set_x(pos.x);
	this->corps.body->SetLinearVelocity(b2Vec2(this->get_vitesse_x(), 0));
	return true;
}

void Vehicules::draw_circle(double x, double r, sf::RenderWindow& window)
{
	int y;
	if (this->position_y == haute) y = 85;
	else if (this->position_y == milieu) y = 50;
	else y = 15;
	sf::CircleShape shape(static_cast<float>(r));
	shape.setFillColor(sf::Color::White);
	shape.setPosition(static_cast<float>(x - r), static_cast<float>(WINDOW_HEIGHT / 2 - (y + r)));
	window.draw(shape);
}
