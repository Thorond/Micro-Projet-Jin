#include "Camions.hpp"

Camions::Camions(double x, double vitesse/*, position_route position*/, niveau niveau)
	: Vehicules(x, vitesse/*, position*/)
{
	this->construction_pare_choc(niveau);
}

void Camions::construction_pare_choc(niveau niveau) {
	if (niveau == un) {
		this->set_etat_pc_avant(bon);
		this->set_etat_pc_arriere(bon);
	}
	else if (niveau == deux) {
		this->set_etat_pc_avant(excellent);
		this->set_etat_pc_arriere(excellent);
	}
	else {
		this->set_etat_pc_avant(indestructible);
		this->set_etat_pc_arriere(indestructible);
	}
}