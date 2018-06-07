
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
	this->set_y();
}

Vehicules::~Vehicules() {

}


double Vehicules::get_x() { return x; }
void Vehicules::set_x(double x) {
	this->x = x;
}

double Vehicules::get_y() { return y; }
void Vehicules::set_y() {
	if ( this->position_y == haute) this->y = POSITIONNEMENT_VOIE_HAUTE;
	else if (this->position_y == milieu) this->y = POSITIONNEMENT_VOIE_MILIEU;
	else this->y = POSITIONNEMENT_VOIE_BASSES;
}

double Vehicules::get_vitesse_x() { return vitesse_x; }
void Vehicules::set_vitesse_x(double vitesse) {
	this->vitesse_x = vitesse;
}

void Vehicules::set_longueur(int longueur) { this->longueur = longueur; }
double Vehicules::get_longueur() { return longueur;  }

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
	if (this->get_x() + LONGUEUR_VOITURE * 2 > vehiDevant.get_x()  && vehiDevant.get_vitesse_x() < this->get_vitesse_x() ) {
		this->set_vitesse_x(vehiDevant.get_vitesse_x() );
		this->corps.body->SetLinearVelocity(b2Vec2((float32)vehiDevant.get_vitesse_x(), 0));
	}
}

/* fonction qui permet de synchroniser les valeurs par defaut du constructeur et celle du body de box2d*/
bool Vehicules::Update(sf::RenderWindow& window) {
	b2Vec2 pos = this->corps.body->GetPosition();
	this->set_x(pos.x);
	this->corps.body->SetLinearVelocity(b2Vec2((float32)this->get_vitesse_x(), 0));
	return true;
}

void Vehicules::draw_circle(double x, double y, double r, sf::RenderWindow& window)
{
	sf::CircleShape shape(static_cast<float>(r));
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(3);
	shape.setOutlineColor(sf::Color::Black);
	shape.setPosition(static_cast<float>(x - r), static_cast<float>( (y - r)));
	window.draw(shape);
}

void Vehicules::draw_rectangle(double x, double y, double dx, double dy, sf::RenderWindow& window)
{
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f((float)dx, (float)dy));
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(3);
	shape.setPosition(static_cast<float>(x), static_cast<float>(y ));
	window.draw(shape);
}
