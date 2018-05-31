#pragma once
#include "Vehicules.hpp"

class Voitures : public Vehicules
{

public :
	Voitures(double x, double vitesse/*, position_route position*/, niveau niveau);
	void construction_pare_choc(niveau niveau) override;

};