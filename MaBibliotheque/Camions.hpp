#pragma once
#include "Vehicules.hpp"

class Camions : public Vehicules
{

public:
	Camions(double x, double vitesse/*, position_route position*/, niveau niveau);
	void construction_pare_choc(niveau niveau) override;

}; 
