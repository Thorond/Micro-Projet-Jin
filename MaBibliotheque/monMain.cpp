#include "stdafx.h"
#include "monMain.h"
#include "Route.hpp"
#include <iostream>
#include "Draw.hpp"

int monMain()
{
	/*Voitures vehi = Voitures(500, 70,un);
	std::cout << vehi.get_etat_pc_arriere() << std::endl;
	vehi.set_etat_pc_arriere( (etat_pare_choc)(vehi.get_etat_pc_arriere()+1));
	std::cout << vehi.get_etat_pc_arriere() << std::endl;*/


	SFML_output out;
	out.draw_circle(50, 50);
	out.display();

	return 0;
}