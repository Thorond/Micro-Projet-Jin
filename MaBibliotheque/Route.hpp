#pragma once
#include "Joueur.hpp"
#include "Camions.hpp"
#include <vector>
#include <memory>
#include <random>
#include <iostream>

class Route 
{
public :
	Route();
	etat_du_jeu get_etat();
	void set_etat(etat_du_jeu nouvEtat);
	int get_distance_parcouru();
	void set_distance_parcouru(int dist);
	niveau get_niveau(); 
	void set_niveau(niveau nouvNiv);

	b2World* get_world();

	int get_index_voiture_joueur();
	void set_index_voiture_joueur(int index);
	position_route get_position_voiture_joueur();
	void set_position_voiture_joueur(position_route pos);
	std::vector<std::unique_ptr<Vehicules>>& get_voie_voiture(position_route pos );

	std::vector<std::unique_ptr<Vehicules>>& get_voie_haute();
	std::vector<std::unique_ptr<Vehicules>>& get_voie_milieu();
	std::vector<std::unique_ptr<Vehicules>>& get_voie_basse();
	
	Vehicules* get_vehicule(std::vector<std::unique_ptr<Vehicules>>& voie, int rang);
	Vehicules* get_vehicule(position_route pos, int rang);
	
	void gestion_global(sf::Clock& clock, sf::Time& elapsed);
	void reinit_global(); /* Fonction de réinitialisation pour une nouvelle partie*/
	void generation_automatique(sf::Clock& clock , sf::Time& elapsed); /*générer pour les trois voies une voiture ou un camion de
	façon régulière */
	void generation_vehicules( position_route posi); /* creation de l'unique pointer et ajout dans un des vecteur */

	/* Cette fonction permet de changer de voie une voiture (juste le joueur au final) 
	Elle verifie aussi qu'un vehicule n'est pas present au meme niveau que le vehicule changeant de voie, sur la voie ou
	il se dirige. **Pour les camions, il faut la retravailler car il prend soit trop de marge soit pas assez.** */
	bool changer_de_voie(position_route choix, position_route posActuel, Vehicules& vehic, bool is_joueur);
	bool changer_de_voie_haut_joueur(); /* Utile pour gerer les evenements en fonction de la position du joueur*/
	bool changer_de_voie_bas_joueur(); /* Utile pour gerer les evenements en fonction de la position du joueur*/
	void nettoyage_voies(); /* On vide les trois vecteurs pour relancer une partie*/
	void passage_de_niveau(); /* Lorsque le joueur arrive à un certain point, il passe au niveau supérieur*/

	/* Fonction primordiale permettant de mettre à jour la position des vehicules ainsi que de celui du joueur, 
	grace a box2D, de supprimer les vehicules en dehors des limites et d'appeler les fonctions principales 
	des vehicules tels que 'adapter_sa_vitesse'.*/
	void Update();
	void draw(sf::RenderWindow& window);

	/* Fonction gerant la voiture du joueur et donc ce dernier meme quant au jeu, lancant le gameover si celui ci
	n'a plus de 'vie', etc. */
	void gestion_voiture_joueur();
	/* Reinitialisation des donnees du joueur lors d'un lancement de jeu/gameover. */
	void reinit_donnees_joueur();



private :
	etat_du_jeu etat_en_cours;
	int distance_parcouru;
	niveau niveau_route;
	std::vector<std::unique_ptr<Vehicules>> voie_haute;
	std::vector<std::unique_ptr<Vehicules>> voie_milieu;
	std::vector<std::unique_ptr<Vehicules>> voie_basse;

	b2World * world;

	int unsigned index_voiture_joueur;
	position_route position_voiture_joueur;

};