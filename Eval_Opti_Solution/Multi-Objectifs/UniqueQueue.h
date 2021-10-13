#pragma once

#include <queue>
#include <set>
#include <vector>

class UniqueQueue {
public:
	std::set<int> unique_sommets;
	std::queue<int> queue;
	std::vector<std::vector<int>> labels_sommet;

	UniqueQueue() {}

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
		labels_sommet[sommet].clear();
	}

	int defiler_sans_clear() {
		int sommet = queue.front();
		queue.pop();
	}

	void verify_no_exec() {
		std::vector<int> to_erase;
		std::set<int>::iterator it;
		for (it = unique_sommets.begin(); it != unique_sommets.end(); it++)
			if (labels_sommet[*it].size() == 0) to_erase.push_back(*it);
		for (int i = 0; i < to_erase.size(); i++) unique_sommets.erase(to_erase[i]);
		std::queue<int> new_queue;
		while (queue.size() != 0) {
			int sommet = defiler_sans_clear();
			if (unique_sommets.find(sommet) == unique_sommets.end())
				new_queue.push(sommet);
		}
		queue = new_queue;
	}
};