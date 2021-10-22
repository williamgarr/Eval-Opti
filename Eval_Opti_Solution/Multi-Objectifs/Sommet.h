#pragma once

#include <vector>
#include <map>
#include "Label.h"
#include "Config.h"

/// <summary>
/// Comparison function for labels
/// </summary>
/// <param name="gauche">Left label</param>
/// <param name="droit">Right label</param>
/// <returns>
/// Return code (see in function)
/// </returns>
int comparer_label(Label gauche, Label droit) {
	// 0 -> gauche ? droit
	// 1 -> gauche < droit
	// 2 -> gauche > droit
	// 3 -> gauche = droit

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
	// node unique number
	int numero_sommet;
	
	// successor nodes list (not used)
	std::vector<int> successeurs;

	// map of the successors and values (key = successor node unique number, value = pair of longueur and cout to the successor)
	std::map<int, std::pair<double, double>> quick_access;

	// map of the labels on the node (key = label unique number, value = the label)
	std::map<int, Label> labels;

	Sommet(int num) : numero_sommet(num) {}
	
	// Add a successor (not usefull)
	void ajouter_successeur(int num) {
		successeurs.push_back(num);
	}

	/// <summary>
	/// Function to propagate a label on the current label
	/// </summary>
	/// <param name="l">Label to propagate</param>
	void inserer_label(Label l) {
		// si l dominé par label dans la liste -> arrêter, pas d'insert
		// si l domine un label dans la liste -> supprimer le label (attention algorithme à l'algorithme à pile -> supprimer sommet dans la pile si le label est le seul qui doit être exec)
		
		// for each label on the destination :
		// * compare the two labels
		// * if l dominated -> quit the function
		// * if l dominate a label -> delete the label dominated from the map
		// * after delete of useless labels if l is not dominated insert it into the map
		std::map<int, Label>::iterator it;
		std::vector<int> to_erase;
		for (it = labels.begin(); it != labels.end(); it++) {
			int cmp = comparer_label(l, (*it).second);
			if (cmp == 2 || cmp == 3) return; // si l dominé ou l = p (l existe déjà dans la liste)
			if (cmp == 1)  to_erase.push_back((*it).second.chemin[(*it).second.chemin.size()-1]); // si l domine un label existant
		}

		// labels deletion
		for (unsigned int i = 0; i < to_erase.size(); i++) {
			labels.erase(to_erase[i]);
			algo_queue.nb_labels[to_erase[i]]--;
		}
		
		// label l insertion
		algo_queue.enfiler(numero_sommet);
		algo_queue.nb_labels[numero_sommet]++;
		labels.insert(std::pair<int, Label>(l.numero_label, l));
		if (debug) std::cout << "MILESTONE : Insertion label n°" << l.numero_label << " > sommet n°" << numero_sommet << std::endl;
	}
};