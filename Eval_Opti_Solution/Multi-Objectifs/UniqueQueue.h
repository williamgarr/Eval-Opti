#pragma once

#include <queue>
#include <set>
#include <vector>
#include "Config.h"

// WARNING : MUST BE SUPERIOR TO THE NUMBER OF NODES
#define TAILLE_MAX 1000

class UniqueQueue {
public:
	// unique set of the nodes currently in the queue
	std::set<int> unique_sommets;

	// processing queue without duplicates nodes
	std::queue<int> queue;

	// number of labels on each node : nb_labels[0] -> number of labels on node 0
	int nb_labels[TAILLE_MAX];

	UniqueQueue() {
		for (int i = 0; i < TAILLE_MAX; i++) nb_labels[i] = 0;
	}

	// Add a node to the queue (only if not present in queue)
	void enfiler(int sommet) {
		if (unique_sommets.find(sommet) == unique_sommets.end()) {
			unique_sommets.insert(sommet);
			queue.push(sommet);
		}
	}

	// Remove and return the next node to process from the queue (WARNING : no verification if empty)
	int defiler() {
		int sommet = queue.front();
		queue.pop();
		unique_sommets.erase(sommet);
		nb_labels[sommet] = 0;
		return sommet;
	}

	// Remove and return the next node without clearing the set and label number (used for internal processing)
	int defiler_sans_clear() {
		int sommet = queue.front();
		queue.pop();
		return sommet;
	}

	// Remove from queue the nodes with no labels to process
	void verify_no_exec() {
		// find nodes in the queue (within the set) with no labels to process
		std::vector<int> to_erase;
		std::set<int>::iterator it;
		for (it = unique_sommets.begin(); it != unique_sommets.end(); it++)
			if (nb_labels[*it] == 0) to_erase.push_back(*it);

		// Delete useless labels to process from the set
		for (unsigned int i = 0; i < to_erase.size(); i++) unique_sommets.erase(to_erase[i]);
		
		// Recreate the queue without the useless labels to process
		std::queue<int> new_queue;
		while (queue.size() != 0) {
			int sommet = defiler_sans_clear();
			if (unique_sommets.find(sommet) != unique_sommets.end())
				new_queue.push(sommet);
		}
		queue = new_queue;
	}

	// Display the queue for debug
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