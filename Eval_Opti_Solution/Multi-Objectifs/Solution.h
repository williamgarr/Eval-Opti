#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "Sommet.h"
#include "Label.h"
#include "Config.h"

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
				if (debug) std::cout << "DEBUG : Sommet N°" << numero_noeud << " [";

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
				if (debug) std::cout << "DEBUG : Arc N°" << numero_arc << " ; From = " << from << " ; To = " << to << " ; Longueur = " << longueur << " ; Cout = " << cout << std::endl;
				sommets[from].ajouter_arc(a);
			}
			std::cout << "MILESTONE : Fin de lecture du fichier" << std::endl;
		}
		else
			std::cout << "ERREUR : Ouverture du fichier" << std::endl;
	}

	void exec(std::string fichier) {
		lecture_fichier(fichier);
		for (unsigned int i = 0; i < sommets.size(); i++) sommets[i].preprocess_successeurs();
		std::cout << "MILESTONE : Préprocess terminé" << std::endl;

		algo_queue.enfiler(depart);
		Label l_depart(prochain_numero_label, 0, 0);
		prochain_numero_label++;
		sommets[depart].inserer_label(l_depart);
		std::cout << "MILESTONE : Initialisation terminé" << std::endl;

		while (!algo_queue.queue.empty()) {
			int sommet_en_cours = algo_queue.defiler();
			std::cout << "MILESTONE : Début process sommet n°" << sommet_en_cours << std::endl;
			for (unsigned int i = 0; i < sommets[sommet_en_cours].labels.size(); i++) {
				Label L = sommets[sommet_en_cours].labels[i];
				if (debug) L.afficher_label();
				std::map<int, std::pair<double, double>>::iterator it;
				for (it = sommets[sommet_en_cours].quick_access.begin(); it != sommets[sommet_en_cours].quick_access.end(); it++) {
					int succ = (*it).first;
					std::cout << "MILESTONE : Process " << sommet_en_cours << "/" << succ << std::endl;
					double longueur = (*it).second.first;
					double cout = (*it).second.second;
					Label P(prochain_numero_label, L.longueur + longueur, L.cout + cout);
					prochain_numero_label++;
					if (debug) P.afficher_label();
					P.ajouter_sommet(L, succ);
					sommets[succ].inserer_label(P);
				}
			}
			algo_queue.verify_no_exec();
		}
	}

};