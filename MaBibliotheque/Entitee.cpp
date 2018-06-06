#include "Entitee.hpp"

Entitee::Entitee(b2World& world) {
	this->world = &world;
}

void Entitee::charger(double x, double y, double vitesse, bool isCamion) {
	this->body_def = new b2BodyDef();
	this->body_def->type = b2_kinematicBody;
	this->body_def->position.Set(x,y);
	this->body = this->world->CreateBody(this->body_def);

	// On utilise pas ceci mais on doit quand même le créé 
	this->shape = new b2PolygonShape();
	if (!isCamion) {
		this->shape->SetAsBox(1, 1);
	}
	else {
		this->shape->SetAsBox(1, 1);
	}

	this->fixture_def = new b2FixtureDef();
	this->fixture_def->shape = this->shape;

	this->fixture_def->density = 1.0f;
	this->body->CreateFixture(this->fixture_def);

	this->body->SetLinearVelocity(b2Vec2(vitesse, 0));
}


Entitee::~Entitee() {
	delete this->body_def;
	delete this->shape;
	delete this->fixture_def;
}

