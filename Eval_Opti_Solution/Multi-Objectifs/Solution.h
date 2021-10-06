#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Sommet.h"
#include "Label.h"

class Solution {
public:
	int nombre_noeud;
	int nombre_arc;
	std::vector<Sommet> sommets;

	Solution() : nombre_noeud(0), nombre_arc(0) {}

	void lecture_fichier(std::string nom_fichier) {
		std::ifstream flux(nom_fichier.c_str());

		if (flux) {
			std::cout << "MILESTONE : Fichier ouvert" << std::endl;
			flux >> nombre_noeud;
			flux >> nombre_arc;
			std::cout << "MILESTONE : Nb noeuds = " << nombre_noeud << " ; Nb arcs = " << nombre_arc << std::endl;
			for (int i = 0; i < nombre_noeud; i++) {
				int numero_noeud;
				flux >> numero_noeud;
				Sommet s(numero_noeud);
				if (debug) std::cout << "DEBUG : Sommet n°" << numero_noeud << " [";

				std::string successeur;
				flux >> successeur;
				while (successeur != "*") {
					s.ajouter_successeur(atoi(successeur.c_str()));
					if (debug) std::cout << successeur << " ";
					flux >> successeur;
				}
				if (debug) std::cout << "]" << std::endl;
				sommets.push_back(s);
			}

			for (int i = 0; i < nombre_arc; i++) {
				int numero_arc, from, to;
				double longueur, cout;
				flux >> numero_arc;
				flux >> from;
				flux >> to;
				flux >> longueur;
				flux >> cout;
				Arc a(numero_arc, from, to, longueur, cout);
				if (debug) std::cout << "DEBUG : Arc n°" << numero_arc << " ; From = " << from << " ; To = " << to << " ; Longueur = " << longueur << " ; Cout = " << cout << std::endl;
				sommets[from].ajouter_arc(a);
			}
			std::cout << "MILESTONE : Fin de lecture du fichier" << std::endl;
		}
		else
			std::cout << "ERREUR : Ouverture du fichier" << std::endl;
	}


};

/**
* 0 -> gauche ? droit
* 1 -> gauche < droit
* 2 -> gauche > droit
* 3 -> gauche = droit
*/
int comparer_label(Label gauche, Label droit) {
	int nl = 1;
	int np = 2;
	if ((gauche.longueur < droit.longueur) || (gauche.cout < droit.cout))
		np = 0;
	if ((droit.longueur < gauche.longueur) || (droit.cout < gauche.cout))
		nl = 0;
	return nl + np;
}