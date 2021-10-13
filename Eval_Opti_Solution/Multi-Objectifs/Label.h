#pragma once

class Label {
public:
	int numero_label;
	double longueur;
	double cout;
	std::vector<int> chemin;

	Label(int num, double l, double c) : numero_label(num), longueur(l), cout(c) {}

	void ajouter_sommet(Label prec, int sommet) {
		chemin = prec.chemin;
		chemin.push_back(sommet);
	}

	void afficher_label() {
		std::cout << "Label N°" << numero_label << " : Longueur = " << longueur << " ; Cout = " << cout << std::endl;
		if (chemin.size() > 0) {
			std::cout << "Chemin = ";
			for (int i = 0; i < chemin.size(); i++) {
				std::cout << chemin[i] << " ";
			}
			std::cout << std::endl;
		}
	}
};