#pragma once
enum position_route { haute, milieu, basse };
enum etat_pare_choc { détruit, abime, bon , excellent, indestructible, indefini};
enum niveau { un, deux, trois }; // à placer autre part

class Vehicules
{
public:
	Vehicules(double x, double vitesse/*, position_route position*/);
	//~Vehicules();
	double get_x();
	void set_x( double x);
	double get_vitesse_x();
	void set_vitesse_x( double vitesse );
	/*position_route get_position();
	void set_position( position_route position);*/
	etat_pare_choc get_etat_pc_avant();
	void set_etat_pc_avant(etat_pare_choc etat);
	etat_pare_choc get_etat_pc_arriere();
	void set_etat_pc_arriere(etat_pare_choc etat);



	// formes (sfml)


private:
	double x;
	double vitesse_x;
	//position_route position_y;
	etat_pare_choc etat_pc_avant;
	etat_pare_choc etat_pc_arriere;
};