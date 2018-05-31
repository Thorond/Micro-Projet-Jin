#include "pch.h"
#include "../MaBibliotheque/Route.hpp"

TEST(TestGenerationVoiture, TestStatique) {
	Route route = Route();
	route.generation_vehicules(route.get_voie_basse());
	route.get_vehicule(route.get_voie_basse(), 0)->set_vitesse_x(80);
	route.get_vehicule(route.get_voie_basse(), 0)->set_x(550);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 0)->get_vitesse_x(), 80);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 0)->get_x(), 550);
}

TEST(TestConsColli, TestStatique1) {
	Route route = Route();
	route.generation_vehicules(route.get_voie_basse());
	route.get_vehicule(route.get_voie_basse(), 0)->set_vitesse_x(80);
	route.get_vehicule(route.get_voie_basse(), 0)->set_x(450);
	route.generation_vehicules(route.get_voie_basse());
	route.get_vehicule(route.get_voie_basse(), 0)->set_etat_pc_avant((etat_pare_choc)0);
	route.get_vehicule(route.get_voie_basse(), 1)->set_etat_pc_arriere((etat_pare_choc)0);
	route.consequence_collision(*route.get_vehicule(route.get_voie_basse(), 0),
		*route.get_vehicule(route.get_voie_basse(), 1));
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 0)->get_etat_pc_avant(), 0);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 1)->get_etat_pc_arriere(), 0);

	route.get_vehicule(route.get_voie_basse(), 0)->set_etat_pc_avant((etat_pare_choc)3);
	route.get_vehicule(route.get_voie_basse(), 1)->set_etat_pc_arriere((etat_pare_choc)1);
	route.consequence_collision(*route.get_vehicule(route.get_voie_basse(), 0),
		*route.get_vehicule(route.get_voie_basse(), 1));
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 0)->get_etat_pc_avant(), 2);
	EXPECT_LE(route.get_vehicule(route.get_voie_basse(), 1)->get_etat_pc_arriere(), 0);
}


TEST(TestMouvement, TestDynamique1) {
	Route route = Route();
	route.generation_vehicules(route.get_voie_basse());
	Vehicules* temp = route.get_vehicule(route.get_voie_basse(), 0);
	EXPECT_EQ(temp->get_x(), 500);
	EXPECT_EQ(temp->corps.body->GetPosition().x, 500);
	b2Vec2 vel = temp->corps.body->GetLinearVelocity();
	//temp->corps.body->ApplyForceToCenter(b2Vec2(-1000, 0), true);
	//temp->corps.body->SetLinearVelocity(b2Vec2(-1000, 0));
	temp->corps.body->SetTransform(b2Vec2(-50, 0), 0);
	sf::sleep(sf::milliseconds(1000));
	temp->Update();
	EXPECT_LT(temp->corps.body->GetPosition().x, 500);
}