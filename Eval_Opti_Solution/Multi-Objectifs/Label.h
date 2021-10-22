#pragma once

class Label {
public:
	// label unique number
	int numero_label;

	// label summed longueur
	double longueur;

	// label summed cout
	double cout;

	// label history node path (list) : ex. 0 -> 1 -> 4 -> 7 -> 9
	std::vector<int> chemin;

	Label() : numero_label(-1), longueur(-1), cout(-1) {}

	Label(int num, double l, double c) : numero_label(num), longueur(l), cout(c) {}

	/// <summary>
	/// Add a node to the path history of the label
	/// </summary>
	/// <param name="prec">Parent label for initial path copy</param>
	/// <param name="sommet">Node to add to path</param>
	void ajouter_sommet(Label prec, int sommet) {
		chemin = prec.chemin;
		chemin.push_back(sommet);
	}

	// Display the label in std::cout
	void afficher_label() {
		std::cout << "Label N°" << numero_label << " : Longueur = " << longueur << " ; Cout = " << cout << std::endl;
		if (chemin.size() > 0) {
			std::cout << "Chemin = ";
			for (unsigned int i = 0; i < chemin.size(); i++) {
				std::cout << chemin[i] << " ";
			}
			std::cout << std::endl;
		}
	}
};