// Multi-Objectifs.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include "Config.h"
#include "Solution.h"

void test_label() {
    Label l1(0, 10, 5);
    Label l2(1, 5, 10);
    Label l3(2, 5, 5);
    // l1 l1 3 
    std::cout << comparer_label(l1, l1) << std::endl;
    // l1 l2 0 
    std::cout << comparer_label(l1, l2) << std::endl;
    // l1 l3 2 
    std::cout << comparer_label(l1, l3) << std::endl;
    // l3 l1 1 
    std::cout << comparer_label(l3, l1) << std::endl;
}

void test_decaler_gauche() {
    std::vector<int> l;
    for (int i = 0; i < 10; i++) {
        l.push_back(i);
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 4; i < l.size() - 1; i++) {
        l[i] = l[i + 1];
    }
    for (int i = 0; i < l.size(); i++) {
        std::cout << i << " ";
    }
}

void test() {
    std::vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
        std::cout << i << " ";
    } std::cout << std::endl;
    for (int i = 0; i < v.size(); i++) {
        std::cout << i << " ";
    } std::cout << std::endl;
}

int main()
{
    std::cout << "Program start-up" << std::endl;
    std::string fichier = "test.dat";
    Solution s;
    debug = true;
    // s.lecture_fichier(fichier);

    // test_decaler_gauche();
    test();
}
