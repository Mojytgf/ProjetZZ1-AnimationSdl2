
#ifndef FOURMIE
#define FOURMIE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>
#include "graphe.h"


#define NUM_ANTS 500
#define ALPHA 1.0
#define BETA 2.0
#define Q 0.5


int selectNextCity(int currentCity, int visited[MATRIX_SIZE], double pheromones[MATRIX_SIZE][MATRIX_SIZE], double distances[MATRIX_SIZE][MATRIX_SIZE]);

void updatePheromoneMatrix(double pheromones[MATRIX_SIZE][MATRIX_SIZE], int ants[NUM_ANTS][MATRIX_SIZE], double pheromoneIncrement[NUM_ANTS]);

void initializePheromoneMatrix(double pheromones[MATRIX_SIZE][MATRIX_SIZE]);

int antColonyOptimization(double pheromones[MATRIX_SIZE][MATRIX_SIZE], double distances[MATRIX_SIZE][MATRIX_SIZE], int bestSolution[MATRIX_SIZE]);


#endif
