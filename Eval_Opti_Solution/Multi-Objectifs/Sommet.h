#pragma once

#include <vector>
#include "Arc.h"
#include "Label.h"

class Sommet {
public:
	int numero_sommet;
	std::vector<int> successeurs;
	std::vector<Arc> arcs;
	std::vector<Label> labels;

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
		labels.push_back(Label(num, l, c));
	}

	void ajouter_label(Label l) {
		labels.push_back(l);
	}
};