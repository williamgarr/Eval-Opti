#pragma once

#include "UniqueQueue.h"

// Variable de debug : affiche des informations complémentaires lors de l'ex�cution
int debug = false;

// Retention des labels : indique le nombre de label maximum à garder dans chaque sommet
int retention_label = 10;

// Numero de départ des labels
int prochain_numero_label = 0;

// Sommet de départ
int depart = 0;

// Sommet d'arrivé
int arrive = 199;

// Queue pour l'algorithme à pile/queue
UniqueQueue algo_queue;