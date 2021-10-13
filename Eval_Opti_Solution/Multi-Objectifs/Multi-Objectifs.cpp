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

void test_list_label() {
    Sommet s(1);
    Label l1(0, 10, 10);
    Label l2(1, 5, 10);
    Label l3(2, 10, 5);
    Label l4(3, 9, 4);
    Label l5(4, 11, 11);

    s.ajouter_label(l1);
    s.ajouter_label(l2);
    s.ajouter_label(l2);
    s.ajouter_label(l3);
    s.ajouter_label(l4);
    s.ajouter_label(l5);

    std::map<int, Label>::iterator it;
    for (it = s.labels.begin(); it != s.labels.end(); it++)
        (*it).second.afficher_label();
}

void test_file() {

}

int main()
{
    std::cout << "Program start-up" << std::endl;
    std::string fichier = "test.dat";
    Solution s;
    debug = true;
    // s.lecture_fichier(fichier);
    
    // test_label();
    // test_list_label();

}
