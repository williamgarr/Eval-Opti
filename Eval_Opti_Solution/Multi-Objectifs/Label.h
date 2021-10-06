#pragma once

class Label {
public:
	int numero_label;
	double longueur;
	double cout;

	Label(int num, double l, double c) : numero_label(num), longueur(l), cout(c) {}
};