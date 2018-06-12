#pragma once
#include <iostream>   

enum etat_du_jeu {
	en_jeu,
	pause,
	gameover,
	menu_demarrer
};

enum position_route {
	haute,
	milieu,
	basse
};


typedef enum  {
	detruit = 0,
	abime = 1,
	bon = 2,
	excellent = 3,
	indestructible = 4,
	indefini = 5
}etat_pare_choc ;


enum niveau {
	un,
	deux,
	trois
};

static const unsigned int VITESSE_DE_BASE(35);
static const unsigned int VITESSE_DEFILEMENT(45);
static const unsigned int VITESSE_MAX(65 );
static const int VITESSE_MIN(25 );
static const unsigned int VITESSE_MAX_RELATIVE(65 - VITESSE_DEFILEMENT);
static const int VITESSE_MIN_RELATIVE(25 - VITESSE_DEFILEMENT);

static const unsigned int LONGUEUR_VOITURE(40);
static const unsigned int LARGEUR_VOITURE(20); // inutilise ici 
static const unsigned int RAYON_ROUE(5);

static const unsigned int WINDOW_WIDTH(1000);
static const unsigned int WINDOW_HEIGHT(700);

/* Positionnement sur l'axe des y pour l'affichage des vehicules */
static const unsigned int POSITIONNEMENT_VOIE_HAUTE(WINDOW_HEIGHT  / 3);
static const unsigned int POSITIONNEMENT_VOIE_MILIEU(WINDOW_HEIGHT / 2);
static const unsigned int POSITIONNEMENT_VOIE_BASSES(WINDOW_HEIGHT * 2 / 3);

static const double MS_PER_UPDATE(1.6);