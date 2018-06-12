#include "pch.h"
#include "../MaBibliotheque/Route.hpp"
#include "../MaBibliotheque/Draw.hpp"
#include "../MaBibliotheque/Data.cpp"

/* Test verifiant que la generation de vehicule se fait correctement*/
TEST(TestGenerationVoiture, TestStatique) {
	Route route = Route();
	route.generation_vehicules( basse);
	route.get_vehicule(route.get_voie_basse(), 0)->set_vitesse_x(80);
	route.get_vehicule(route.get_voie_basse(), 0)->set_x(550);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 0)->get_vitesse_x(), 80);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 0)->get_x(), 550);
}

/* Tests verifiant que la fonction de colision et de consequence associe fonctionne correctement*/
TEST(TestConsColli, TestStatique1) {
	Route route = Route();
	route.generation_vehicules( basse);
	route.generation_vehicules(basse);
	Voitures* v1 = (Voitures*)route.get_vehicule(route.get_voie_basse(), 0);
	Voitures* v2 = (Voitures*)route.get_vehicule(route.get_voie_basse(), 1);
	v1->set_vitesse_x(80);
	v1->set_x(450);
	v1->set_etat_pc_avant((etat_pare_choc)0);
	v2->set_etat_pc_arriere((etat_pare_choc)0);
	v1->consequence_collision(route.get_voie_basse(), 0,*v2);
	EXPECT_EQ(v1->get_etat_pc_avant(), -1);
	EXPECT_EQ(route.get_voie_basse().size(), 1);

	route.generation_vehicules(basse);
	v2 = (Voitures*)route.get_vehicule(route.get_voie_basse(), 1);
	v1->set_etat_pc_avant((etat_pare_choc)3);
	v2->set_etat_pc_arriere((etat_pare_choc)1);
	v1->consequence_collision(route.get_voie_basse(), 0, *v2);
	EXPECT_EQ(v1->get_etat_pc_avant(), 2);
	EXPECT_EQ(route.get_voie_basse().size(), 1);
}
TEST(TestConsColli, TestStatique2) {
	Route route = Route();
	route.generation_vehicules(basse);
	route.generation_vehicules(basse);
	Voitures* v1 = (Voitures*)route.get_vehicule(route.get_voie_basse(), 0);
	Voitures* v2 = (Voitures*)route.get_vehicule(route.get_voie_basse(), 1);
	v1->set_vitesse_x(80);
	v1->set_x(450);
	v1->set_etat_pc_avant((etat_pare_choc)3);
	v2->set_etat_pc_arriere((etat_pare_choc)1);
	v1->consequence_collision(route.get_voie_basse(), 0, *v2);
	EXPECT_EQ(v1->get_etat_pc_avant(), 2);
	EXPECT_EQ(route.get_voie_basse().size(), 1);
}
TEST(TestConsColli, TestStatique3) {
	Route route = Route();
	route.generation_vehicules(basse);
	route.generation_vehicules(basse);
	Voitures* v1 = (Voitures*)route.get_vehicule(route.get_voie_basse(), 0);
	Voitures* v2 = (Voitures*)route.get_vehicule(route.get_voie_basse(), 1);
	v1->set_vitesse_x(80);
	v1->set_x(450);
	v1->set_etat_pc_avant((etat_pare_choc)1);
	v2->set_etat_pc_arriere((etat_pare_choc)3);
	v1->consequence_collision(route.get_voie_basse(), 0, *v2);
	EXPECT_EQ(v1->get_etat_pc_avant(), -2);
	EXPECT_EQ(v2->get_etat_pc_arriere(), 2);
}

/* Test verifiant que box2d est correctement implente*/
TEST(TestCorp, TestStatique1) {
	Route route = Route();
	route.generation_vehicules( basse);
	Vehicules* temp = route.get_vehicule(route.get_voie_basse(), 0);
	EXPECT_EQ(temp->get_x(), WINDOW_WIDTH + 100);
	EXPECT_EQ(temp->corps.body->GetPosition().x, WINDOW_WIDTH + 100);
}

/* Test verifiant que box2d est correctement implente et que le moteur tourne*/
TEST(TestCorp, TestDynamique1) {
	Route route = Route();

	SFML_output out;
	route.generation_vehicules( basse);
	Vehicules* temp = route.get_vehicule(route.get_voie_basse(), 0);
	b2Vec2 vel = temp->corps.body->GetLinearVelocity();
	for (int32 i = 0; i < 60; ++i)
	{
		route.Update();
	}
	EXPECT_NE(vel.x, 0);
	EXPECT_NE(temp->corps.body->GetPosition().x, 500);
}

/* Test verifiant que les véhicules adaptent bien leur vitesse en fonction du vehicule en face */
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
	vehi2->set_x(400 + LONGUEUR_VOITURE);

	EXPECT_NE(vehi1->corps.body->GetLinearVelocity().x, vehi2->corps.body->GetLinearVelocity().x);
	for (int32 i = 0; i < 60; ++i)
	{
		route.Update();
	}
	EXPECT_EQ(vehi1->corps.body->GetLinearVelocity().x, vehi2->corps.body->GetLinearVelocity().x);
}

/* Test permettant de verifier que les vehicules se détruisent bien en sortant de l'écran du joueur */
TEST(TestAI, TestDestruction1) {
	Route route = Route();

	SFML_output out;

	route.generation_vehicules( basse);
	route.get_vehicule(route.get_voie_basse(), 0)->set_x(0);
	EXPECT_EQ(route.get_voie_basse().size(), 1);
	double x = route.get_vehicule(route.get_voie_basse(), 0)->get_x();
	while (x > - 100 ) {
		x = route.get_vehicule(route.get_voie_basse(), 0)->get_x();
		route.Update();
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
	route.get_vehicule(route.get_voie_basse(), 0)->set_x(400);
	route.get_vehicule(route.get_voie_basse(), 1)->set_x(800);
	route.get_vehicule(route.get_voie_milieu(), 1)->set_x(600);
	bool success = route.changer_de_voie(basse, milieu, *route.get_vehicule(route.get_voie_milieu(), 1), false) ;
	EXPECT_EQ(success, true); 
	EXPECT_EQ(route.get_voie_milieu().size(), 1); // le joueur
	EXPECT_EQ(route.get_voie_basse().size(), 3);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 0)->get_x(), 400);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 1)->get_x(), 600);
	EXPECT_EQ(route.get_vehicule(route.get_voie_basse(), 2)->get_x(), 800);
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

/*Test permettant de vérifier le bon fonctionnement du select et de l'update de la DB*/
TEST(TestDB, TestFetchAndChange1) {
	SQLite sqlite = SQLite();
	if (sqlite.get_rc()) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(sqlite.get_db()));
		sqlite3_close(sqlite.get_db());
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}
	Route route = Route();
	sqlite.update_op(1);
	EXPECT_EQ(NIVEAU_DATA, 1);
	sqlite.select_op(route);
	EXPECT_EQ(route.get_niveau(), 1);
	sqlite.update_op(3);
	sqlite.select_op(route);
	EXPECT_EQ(route.get_niveau(), 3);
	sqlite.update_op(1); // pour remettre la valeur à 1 dans le fichier

	sqlite3_close(sqlite.get_db());
}