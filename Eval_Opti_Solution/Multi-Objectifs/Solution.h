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
	// number of nodes
	int nombre_noeud;

	// number of arcs
	int nombre_arc;

	// nodes list : sommets[0] -> node 0
	std::vector<Sommet> sommets;

	Solution() : nombre_noeud(0), nombre_arc(0) {}

	void lecture_fichier(std::string nom_fichier) {
		// open the file stream
		std::ifstream flux(nom_fichier.c_str());

		// if the stream is up
		if (flux) {
			std::cout << "MILESTONE : Fichier ouvert" << std::endl;

			// get the number of node and arcs
			flux >> nombre_noeud;
			flux >> nombre_arc;
			std::cout << "MILESTONE : Nb noeuds = " << nombre_noeud << " ; Nb arcs = " << nombre_arc << std::endl;

			// read the nodes
			for (int i = 0; i < nombre_noeud; i++) {
				int numero_noeud;
				flux >> numero_noeud;
				Sommet s(numero_noeud);
				if (debug) std::cout << "DEBUG : Sommet N°" << numero_noeud << " [";

				// read the node successors
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

			// read the arcs
			for (int i = 0; i < nombre_arc; i++) {
				int numero_arc, from, to;
				double longueur, cout;
				flux >> numero_arc;
				flux >> from;
				flux >> to;
				flux >> longueur;
				flux >> cout;
				if (debug) std::cout << "DEBUG : Arc N°" << numero_arc << " ; From = " << from << " ; To = " << to << " ; Longueur = " << longueur << " ; Cout = " << cout << std::endl;
				std::pair<double, double> arc_values(longueur, cout);
				// arcs stored in the starting node with a map (key = destination node ; value = pair of longueur and cout)
				sommets[from].quick_access.insert(std::pair<int, std::pair<double, double>>(to, arc_values));
			}

			// close stream
			flux.close();
			std::cout << "MILESTONE : Fin de lecture du fichier" << std::endl;
		}
		else
			std::cout << "ERREUR : Ouverture du fichier" << std::endl;
	}

	void ecriture_fichier(std::string fichier_process) {
		// file name is like "results_<depart>_<arrive>.csv"
		std::string nom_fichier = "results_" + std::to_string(depart) + "_" + std::to_string(arrive) + ".csv";
		std::ofstream flux(nom_fichier);
		flux.clear();

		if (flux) {
			std::cout << "MILESTONE : Fichier ouvert" << std::endl;

			// write results metadata
			flux << "Fichier = " << fichier_process << std::endl;
			flux << "Nombre noeud = " << nombre_noeud << ";Nombre arc = " << nombre_arc << std::endl;
			flux << "Depart = " << depart << ";Arrive = " << arrive << std::endl;
			flux << "no_label;longueur;cout;path" << std::endl;

			// write results informations (destination labels with path)
			std::map<int, Label>::iterator it;
			for (it = sommets[arrive].labels.begin(); it != sommets[arrive].labels.end(); it++) {
				flux << (*it).second.numero_label << ";";
				flux << (*it).second.longueur << ";";
				flux << (*it).second.cout << ";";
				for (unsigned int i = 0; i < (*it).second.chemin.size(); i++)
					flux << (*it).second.chemin[i] << " ";
				flux << '*' << std::endl;
			}

			// close stream
			flux.close();
			std::cout << "MILESTONE : Résultats exportés dans " << nom_fichier << std::endl;
		}
		else
			std::cout << "ERREUR : Ouverture du fichier" << std::endl;
	}

	void exec(std::string fichier) {
		// read the input file
		lecture_fichier(fichier);
		std::cout << "MILESTONE : Préprocess terminé" << std::endl;

		// init the program : add the first label to the starting node
		algo_queue.enfiler(depart);
		Label l_depart(prochain_numero_label, 0, 0);
		prochain_numero_label++;
		sommets[depart].inserer_label(l_depart);
		std::cout << "MILESTONE : Initialisation terminé" << std::endl;

		// while the queue is not empty
		while (!algo_queue.queue.empty()) {
			// get the node to process from the queue
			int sommet_en_cours = algo_queue.defiler();
			std::cout << "MILESTONE : Début process sommet n°" << sommet_en_cours << std::endl;

			// for each label on the node to process
			std::map<int, Label>::iterator it_label;
			for (it_label = sommets[sommet_en_cours].labels.begin(); it_label != sommets[sommet_en_cours].labels.end(); it_label++) {
				// get the currently processed label
				Label L = (*it_label).second;

				// for each successor node of the currently processed node
				std::map<int, std::pair<double, double>>::iterator it;
				for (it = sommets[sommet_en_cours].quick_access.begin(); it != sommets[sommet_en_cours].quick_access.end(); it++) {
					// get the successor node
					int succ = (*it).first;

					// debug : process display
					if (debug) std::cout << "MILESTONE : Process " << sommet_en_cours << "/" << succ << std::endl;

					// get the arc values to processed node to the successor
					double longueur = (*it).second.first;
					double cout = (*it).second.second;

					// create the new label to try to propagate
					Label P(prochain_numero_label, L.longueur + longueur, L.cout + cout);
					prochain_numero_label++; // label number auto increment
					P.ajouter_sommet(L, succ); // label path history

					// debug : new label display
					if (debug) P.afficher_label();

					// propagate the label into the successor
					sommets[succ].inserer_label(P);
				}
			}

			// when all labels on the node have been propagated, verify if delete node with no labels in the processing queue
			algo_queue.verify_no_exec();
		}

		// after process end, export the results into a CSV file
		ecriture_fichier(fichier);
	}

};