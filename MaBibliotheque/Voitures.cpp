#include "Voitures.hpp"

Voitures::Voitures(double x, double vitesse/*, position_route position*/, niveau niveau) 
	: Vehicules(x, vitesse/*, position*/)
{
	this->construction_pare_choc(niveau);
}

void Voitures::construction_pare_choc(niveau niveau) {
	if (niveau == un) {
		this->set_etat_pc_avant(abime);
		this->set_etat_pc_arriere(abime);
	}
	else if (niveau == deux) {
		this->set_etat_pc_avant(bon);
		this->set_etat_pc_arriere(bon);
	}
	else {
		this->set_etat_pc_avant(excellent);
		this->set_etat_pc_arriere(excellent);
	}
}