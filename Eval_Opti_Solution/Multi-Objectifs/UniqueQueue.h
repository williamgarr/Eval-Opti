#pragma once

#include <queue>
#include <set>
#include <vector>
#include "Config.h"

#define TAILLE_MAX 1000

class UniqueQueue {
public:
	std::set<int> unique_sommets;
	std::queue<int> queue;
	int nb_labels[TAILLE_MAX];

	UniqueQueue() {
		for (int i = 0; i < TAILLE_MAX; i++) nb_labels[i] = 0;
	}

	void enfiler(int sommet) {
		if (unique_sommets.find(sommet) == unique_sommets.end()) {
			unique_sommets.insert(sommet);
			queue.push(sommet);
		}
	}

	int defiler() {
		int sommet = queue.front();
		queue.pop();
		unique_sommets.erase(sommet);
		nb_labels[sommet] = 0;
		return sommet;
	}

	int defiler_sans_clear() {
		int sommet = queue.front();
		queue.pop();
		return sommet;
	}

	void verify_no_exec() {
		std::vector<int> to_erase;
		std::set<int>::iterator it;
		for (it = unique_sommets.begin(); it != unique_sommets.end(); it++)
			if (nb_labels[*it] == 0) to_erase.push_back(*it);
		for (unsigned int i = 0; i < to_erase.size(); i++) unique_sommets.erase(to_erase[i]);
		std::queue<int> new_queue;
		while (queue.size() != 0) {
			int sommet = defiler_sans_clear();
			if (unique_sommets.find(sommet) != unique_sommets.end())
				new_queue.push(sommet);
		}
		queue = new_queue;
	}

	void display() {
		std::cout << "DEBUG : Queue =";
		std::queue<int> to_display = queue;
		while (!to_display.empty()) {
			std::cout << " " << to_display.front();
			to_display.pop();
		}
		std::cout << std::endl;
	}
};