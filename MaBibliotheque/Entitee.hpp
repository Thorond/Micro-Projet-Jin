#pragma once
#include <Box2D\Box2D.h>

class Entitee
{
public:
	Entitee(b2World& world);
	void charger(double x, double y,double vitesse, bool isCamion);
	~Entitee();
	b2Body* body;

private:
	
	b2World * world;
	b2BodyDef* body_def;
	b2PolygonShape* shape;
	b2FixtureDef* fixture_def;
};