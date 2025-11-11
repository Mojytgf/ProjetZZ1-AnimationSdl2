#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>
#include "graphe.h"
#include "methode_de_fourmie.h"
/*
void initializePheromoneMatrix(double pheromones[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            pheromones[i][j] = 1.0;
        }
    }
}

double f(double x, double power) {
    return 1.0 / pow(x, power);
}

int selectNextCity(int currentCity, int visited[MATRIX_SIZE], double pheromones[MATRIX_SIZE][MATRIX_SIZE], double distances[MATRIX_SIZE][MATRIX_SIZE]) {
    double probabilities[MATRIX_SIZE] = {0.0};
    double total = 0.0;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        if (visited[i] == 0 && i != currentCity) {
            double pheromone = pow(pheromones[currentCity][i], ALPHA);
            double distance = pow(1.0 / distances[currentCity][i], BETA);
            probabilities[i] = pheromone * distance;
            total += probabilities[i];
        }
    }

    double randValue = (double)rand() / RAND_MAX * total;

    double cumulativeProb = 0.0;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        if (visited[i] == 0 && i != currentCity) {
            cumulativeProb += probabilities[i];
            if (randValue <= cumulativeProb) {
                return i;
            }
        }
    }

    return -1;
}

void updatePheromoneMatrix(double pheromones[MATRIX_SIZE][MATRIX_SIZE], int ants[NUM_ANTS][MATRIX_SIZE], double pheromoneIncrement[NUM_ANTS]) {
    double evaporationRate = 0.1;
    int x, y;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            pheromones[i][j] *= (1.0 - evaporationRate);
        }
    }

    for (int k = 0; k < NUM_ANTS; k++) {
        for (int i = 0; i < MATRIX_SIZE - 1; i++) {
            x = ants[k][i];
            y = ants[k][i + 1];
            pheromones[x][y] += pheromoneIncrement[k];
            pheromones[y][x] += pheromoneIncrement[k];
        }
        x = ants[k][MATRIX_SIZE - 1];
        y = ants[k][0];
        pheromones[x][y] += pheromoneIncrement[k];
        pheromones[y][x] += pheromoneIncrement[k];
    }
}

int antColonyOptimization(double pheromones[MATRIX_SIZE][MATRIX_SIZE], double distances[MATRIX_SIZE][MATRIX_SIZE], int bestSolution[MATRIX_SIZE]) {
    int ants[NUM_ANTS][MATRIX_SIZE] = {0};
    double pheromoneIncrement[NUM_ANTS] = {0.0};
    int bestObjectiveValue = INT_MAX;

    for (int iteration = 0; iteration < 5000; iteration++) {
        for (int ant = 0; ant < NUM_ANTS; ant++) {
            int startCity = rand() % MATRIX_SIZE;
            int visited[MATRIX_SIZE] = {0};
            visited[startCity] = 1;
            ants[ant][0] = startCity;

            for (int step = 1; step < MATRIX_SIZE; step++) {
                int nextCity = selectNextCity(ants[ant][step - 1], visited, pheromones, distances);
                ants[ant][step] = nextCity;
                visited[nextCity] = 1;
            }
        }

        int objectiveValues[NUM_ANTS] = {0};
        for (int ant = 0; ant < NUM_ANTS; ant++) {
            objectiveValues[ant] = calculateObjectiveValue(distances, ants[ant]);
        }

        for (int ant = 0; ant < NUM_ANTS; ant++) {
            if (objectiveValues[ant] < bestObjectiveValue) {
                bestObjectiveValue = objectiveValues[ant];
                for (int i = 0; i < MATRIX_SIZE; i++) {
                    bestSolution[i] = ants[ant][i];
                }
            }
        }

        for (int ant = 0; ant < NUM_ANTS; ant++) {
            pheromoneIncrement[ant] = Q / objectiveValues[ant];
        }

        updatePheromoneMatrix(pheromones, ants, pheromoneIncrement);
    }
    return bestObjectiveValue;
}

*/
