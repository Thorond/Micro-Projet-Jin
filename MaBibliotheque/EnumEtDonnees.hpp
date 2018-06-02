#pragma once

enum position_route {
	haute,
	milieu,
	basse
};


typedef enum  {
	détruit = 0,
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

static const unsigned int VITESSE_DE_BASE(80); // le joueur aura une vitesse ~130, le camion 60, puis +10% et +20%
								// en proportion 0.75 0.20 0.05 (f(des niveaux))
static const unsigned int VITESSE_DEFILEMENT(130);