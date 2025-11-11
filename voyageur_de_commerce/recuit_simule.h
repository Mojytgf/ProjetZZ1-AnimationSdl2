#ifndef RECUIT_SIMULE
#define RECUIT_SIMULE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "graphe.h"

void generateNeighbor(int* tour, int* neighbor);

void simulatedAnnealing(double initialTemperature, double coolingRate, int numIterations, double distances[MATRIX_SIZE][MATRIX_SIZE]);

#endif