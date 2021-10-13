#pragma once

#include <vector>
#include <map>
#include "Arc.h"
#include "Label.h"
#include "Config.h"

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

class Sommet {
public:
	int numero_sommet;
	std::vector<int> successeurs;
	std::vector<Arc> arcs;
	std::map<int, Label> labels;

	Sommet(int num) : numero_sommet(num) {}
	
	void ajouter_successeur(int num) {
		successeurs.push_back(num);
	}

	void ajouter_arc(int num, int to, int longueur, int cout) {
		arcs.push_back(Arc(num, numero_sommet, to, longueur, cout));
	}

	void ajouter_arc(Arc a) {
		arcs.push_back(a);
	}

	void ajouter_label(int num, int l, int c) {
		inserer_label(Label(num, l, c));
	}

	void ajouter_label(Label l) {
		inserer_label(l);
	}

	void inserer_label(Label l) {
		// si l dominé par label dans la liste -> arrêter, pas d'insert
		// si l domine un label dans la liste -> supprimer le label (attention algorithme à l'algorithme à pile -> supprimer sommet dans la pile si le label est le seul qui doit être exec)
		std::map<int, Label>::iterator it;
		std::vector<int> to_erase;
		for (it = labels.begin(); it != labels.end(); it++) {
			int cmp = comparer_label(l, (*it).second);
			if (cmp == 2 || cmp == 3) return; // si l dominé ou l = p (l existe déjà dans la liste)
			if (cmp == 1)  to_erase.push_back((*it).first); // si l domine un label existant
		}

		for (int i = 0; i < to_erase.size(); i++) {
			labels.erase(to_erase[i]);
		}
			
		algo_queue.enfiler(numero_sommet);
		labels.insert(std::pair<int, Label>(l.numero_label, l));
	}
};