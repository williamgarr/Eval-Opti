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

int main()
{
    std::cout << "Program start-up" << std::endl;
    std::string fichier = "test.dat";
    Solution s;
    debug = true;
    s.lecture_fichier(fichier);
}
