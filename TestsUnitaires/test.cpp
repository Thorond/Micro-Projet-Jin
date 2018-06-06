#include "pch.h"
#include "../MaBibliotheque/Route.hpp"
#include "../MaBibliotheque/Draw.hpp"

TEST(TestGenerationVoiture, TestStatique) {
	Route route = Route();
	route.generation_vehicules( basse);
	route.get_vehicule(route.get_voie_basse(), 0)->set_vitesse_x(80);
	route.get_vehicule(route.get_voie_basse(), 0)->set_x(550);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 0)->get_vitesse_x(), 80);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 0)->get_x(), 550);
}

TEST(TestConsColli, TestStatique1) {
	Route route = Route();
	route.generation_vehicules( basse);
	route.get_vehicule(route.get_voie_basse(), 0)->set_vitesse_x(80);
	route.get_vehicule(route.get_voie_basse(), 0)->set_x(450);
	route.generation_vehicules( basse);
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

TEST(TestCorp, TestStatique1) {
	Route route = Route();
	route.generation_vehicules( basse);
	Vehicules* temp = route.get_vehicule(route.get_voie_basse(), 0);
	EXPECT_EQ(temp->get_x(), WINDOW_WIDTH + 100);
	EXPECT_EQ(temp->corps.body->GetPosition().x, WINDOW_WIDTH + 100);
}

TEST(TestCorp, TestDynamique1) {
	Route route = Route();

	SFML_output out;
	route.generation_vehicules( basse);
	Vehicules* temp = route.get_vehicule(route.get_voie_basse(), 0);
	b2Vec2 vel = temp->corps.body->GetLinearVelocity();
	for (int32 i = 0; i < 60; ++i)
	{
		route.Update(out.get_window());
	}
	EXPECT_NE(vel.x, 0);
	EXPECT_NE(temp->corps.body->GetPosition().x, 500);
}

TEST(TestAI, TestDynamique1) {
	Route route = Route();

	SFML_output out;

	route.generation_vehicules( basse);
	Vehicules* vehi1 = route.get_vehicule(route.get_voie_basse(), 0);
	vehi1->set_vitesse_x(10);
	vehi1->corps.body->SetLinearVelocity(b2Vec2(vehi1->get_vitesse_x(), 0));
	vehi1->set_x(400);

	route.generation_vehicules( basse);
	Vehicules* vehi2 = route.get_vehicule(route.get_voie_basse(), 1);
	vehi2->set_vitesse_x(-10);
	vehi2->corps.body->SetLinearVelocity(b2Vec2(vehi2->get_vitesse_x(), 0));
	vehi2->set_x(500);

	EXPECT_NE(vehi1->corps.body->GetLinearVelocity().x, vehi2->corps.body->GetLinearVelocity().x);
	for (int32 i = 0; i < 60; ++i)
	{
		route.Update(out.get_window());
	}
	EXPECT_EQ(vehi1->corps.body->GetLinearVelocity().x, vehi2->corps.body->GetLinearVelocity().x);
}

TEST(TestAI, TestDestruction1) {
	Route route = Route();

	SFML_output out;

	route.generation_vehicules( basse);
	route.get_vehicule(route.get_voie_basse(), 0)->set_x(0);
	EXPECT_EQ(route.get_voie_basse().size(), 1);
	double x = route.get_vehicule(route.get_voie_basse(), 0)->get_x();
	while (x > - 100 ) {
		x = route.get_vehicule(route.get_voie_basse(), 0)->get_x();
		route.Update(out.get_window());
	}
	EXPECT_EQ(route.get_voie_basse().size() , 0);
}

/* Ce test permet de vérifier qu'une voiture qui est appelé par la méthode changer_de_voie
	décrémente bien le vercteur dans lequel elle se trouve et se positionne correctement dans
	le vecteur de la direction ou aller*/
TEST(TestAI, TestDeplacementVoie1) { 
	Route route = Route();

	route.generation_vehicules( basse);
	route.generation_vehicules( basse);
	route.generation_vehicules( milieu);
	route.get_vehicule(route.get_voie_basse(), 0)->set_x(500);
	route.get_vehicule(route.get_voie_basse(), 1)->set_x(600);
	route.get_vehicule(route.get_voie_milieu(), 1)->set_x(550);
	route.changer_de_voie(basse, milieu, *route.get_vehicule(route.get_voie_milieu(), 1), false) ;
	EXPECT_EQ(route.get_voie_milieu().size(), 1); // le joueur
	EXPECT_EQ(route.get_voie_basse().size(), 3);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 0)->get_x(), 500);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 1)->get_x(), 550);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 2)->get_x(), 600);
}

/* Ce test permet de vérifier que la position de la voiture du joueur est bien décrémenter/incrementer quand 
	une voiture se déplace d'une voie à une autre */
TEST(TestAI, TestDeplacementVoie2) {
	Route route = Route();

	route.generation_vehicules(basse);
	route.get_vehicule(route.get_voie_basse(), 0)->set_x(300);
	route.changer_de_voie(milieu, basse, *route.get_vehicule(route.get_voie_basse(), 0), false);
	EXPECT_EQ(route.get_voie_milieu().size(), 2); 
	EXPECT_EQ(route.get_voie_basse().size(), 0);
	EXPECT_EQ(route.get_index_voiture_joueur(), 1);
	route.changer_de_voie(basse, milieu, *route.get_vehicule(route.get_voie_milieu(), 0), false);
	EXPECT_EQ(route.get_voie_milieu().size(), 1);
	EXPECT_EQ(route.get_voie_basse().size(), 1);
	EXPECT_EQ(route.get_index_voiture_joueur(), 0);
}

/* Ce test permet de vérifier qu'une voiture ne peux pas aller sur un voie si une autre voiture est
	déjà présente au même niveau qu'elle */
TEST(TestAI, TestDeplacementVoie3) {
	Route route = Route();

	route.generation_vehicules( basse);
	route.generation_vehicules( basse);
	route.generation_vehicules( milieu);
	route.get_vehicule(route.get_voie_basse(), 0)->set_x(500);
	route.get_vehicule(route.get_voie_basse(), 1)->set_x(500 + LONGUEUR_VOITURE);
	route.get_vehicule(route.get_voie_milieu(), 0)->set_x(500 + LONGUEUR_VOITURE/2);
	EXPECT_EQ(route.changer_de_voie(basse, milieu, *route.get_vehicule(route.get_voie_milieu(), 0), false), false);
}