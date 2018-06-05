#pragma once

enum position_route {
	haute,
	milieu,
	basse
};


typedef enum  {
	d�truit = 0,
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
static const unsigned int VITESSE_DEFILEMENT(40);
static const unsigned int VITESSE_MAX(50 - VITESSE_DEFILEMENT);
static const int VITESSE_MIN(30 - VITESSE_DEFILEMENT);

static const unsigned int LONGUEUR_VOITURE(4);
static const unsigned int LARGEUR_VOITURE(2);

static const unsigned int WINDOW_WIDTH(1000);
static const unsigned int WINDOW_HEIGHT(700);