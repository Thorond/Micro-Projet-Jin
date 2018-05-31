#include "Entitee.hpp"

Entitee::Entitee(b2World& world) {
	this->world = &world;
}

void Entitee::charger(double x, double y) {
	this->body_def = new b2BodyDef();
	this->body_def->type = b2_dynamicBody;
	this->body_def->position.Set(x,y);
	this->body = this->world->CreateBody(this->body_def);

	this->shape = new b2PolygonShape();
	this->shape->SetAsBox(4 * 0.5f - b2_polygonRadius, 2 * 0.5f - b2_polygonRadius); // ***** attention, taille à changer pour les camions **** 

	this->fixture_def = new b2FixtureDef();
	this->fixture_def->shape = this->shape;

	this->fixture_def->density = 1.0f;
	this->body->CreateFixture(this->fixture_def);
}


Entitee::~Entitee() {
	delete this->body_def;
	delete this->shape;
	delete this->fixture_def;
}

