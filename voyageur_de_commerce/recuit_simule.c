#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "graphe.h"
#include "recuit_simule.h"


<<<<<<< HEAD

 // Structure représentant une ville avec ses coordonnées (x, y)
 typedef struct {
     double x;
     double y;
 } City;

 // Fonction pour calculer la distance euclidienne entre deux villes
 double distance(City city1, City city2) {
     double dx = city1.x - city2.x;
     double dy = city1.y - city2.y;
     return sqrt(dx*dx + dy*dy);
 }

 // Fonction pour calculer la longueur totale du trajet
 double tourLength(int* tour, City* cities) {
     double totalLength = 0.0;
    int i;
     for (i = 0; i < NUM_CITIES - 1; i++) {
         int cityIndex1 = tour[i];
        int cityIndex2 = tour[i+1];
        City city1 = cities[cityIndex1];
         City city2 = cities[cityIndex2];
        totalLength += distance(city1, city2);
     }
     // Ajouter la distance entre la dernière ville et la première ville
     int lastCityIndex = tour[NUM_CITIES - 1];
     int firstCityIndex = tour[0];
     City lastCity = cities[lastCityIndex];
    City firstCity = cities[firstCityIndex];
    totalLength += distance(lastCity, firstCity);
     return totalLength;
 }

=======
>>>>>>> fed2135c8e3a1074811af73e598d309ae22480ee
// Fonction pour générer un nouvel état en effectuant un échange de deux villes
void generateNeighbor(int* tour, int* neighbor) {
    int cityIndex1 = rand() % MATRIX_SIZE;
    int cityIndex2 = rand() % MATRIX_SIZE;
    while (cityIndex2 == cityIndex1) {
        cityIndex2 = rand() % MATRIX_SIZE;
    }
    int i;
    for (i = 0; i < MATRIX_SIZE; i++) {
        neighbor[i] = tour[i];
    }
    // Échanger les deux villes sélectionnées
    int temp = neighbor[cityIndex1];
    neighbor[cityIndex1] = neighbor[cityIndex2];
    neighbor[cityIndex2] = temp;
}

// Fonction pour effectuer une itération de l'algorithme du recuit simulé
void simulatedAnnealing(double initialTemperature, double coolingRate, int numIterations, double distances[MATRIX_SIZE][MATRIX_SIZE]) {
    int* currentTour = (int*)malloc(MATRIX_SIZE * sizeof(int));
    int* bestTour = (int*)malloc(MATRIX_SIZE * sizeof(int));
    int i;

    // Initialiser la tournée courante avec l'ordre par défaut (0, 1, 2, ..., NUM_CITIES-1)
    for (i = 0; i < MATRIX_SIZE; i++) {
        currentTour[i] = i;
    }

    // Copier la tournée courante dans la meilleure tournée
    for (i = 0; i < MATRIX_SIZE; i++) {
        bestTour[i] = currentTour[i];
    }

    double currentLength = compareDistancePaths(currentTour, distances);
    double bestLength = currentLength;

    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    double temperature = initialTemperature;

    for (i = 0; i < numIterations; i++) {
        int* neighborTour = (int*)malloc(MATRIX_SIZE * sizeof(int));
        generateNeighbor(currentTour, neighborTour);
        double neighborLength = compareDistancePaths(neighborTour, distances);

        double deltaLength = neighborLength - currentLength;

        if (deltaLength < 0 || exp(-deltaLength / temperature) > ((double)rand() / RAND_MAX)) {
            // Accepter le voisin si sa longueur est meilleure ou selon une probabilité
            for (int j = 0; j < MATRIX_SIZE; j++) {
                currentTour[j] = neighborTour[j];
            }
            currentLength = neighborLength;
        }

        free(neighborTour);

        if (currentLength < bestLength) {
            // Mettre à jour la meilleure tournée
            for (int j = 0; j < MATRIX_SIZE; j++) {
                bestTour[j] = currentTour[j];
            }
            bestLength = currentLength;
        }

        temperature *= coolingRate; // Réduire la température

        // printf("Iteration %d: Best length = %.2f\n", i+1, bestLength);
    }

    // printf("\nBest tour: ");
    // for (i = 0; i < MATRIX_SIZE; i++) {
    //     printf("%d ", bestTour[i]);
    // }
    // printf("\n");
    printf("la longueur du chemin optimale pour la méthode du recuit simulé: %.2f\n", bestLength);

    free(currentTour);
    free(bestTour);
}
<<<<<<< HEAD

int main() {
    int matrice[MATRIX_SIZE][MATRIX_SIZE] = { 0 };
    Node nodes[MATRIX_SIZE];
    double distances[MATRIX_SIZE][MATRIX_SIZE] = { 0 };

    generateRandomPositions(nodes);

    intialiser_matrice(matrice);

    // Calculer les distances entre les sommets
    calculateDistances(nodes, matrice, distances);
    double initialTemperature = 100.0;
    double coolingRate = 0.95;
    int numIterations = 1000;

    simulatedAnnealing(initialTemperature, coolingRate, numIterations, distances);

    return 0;
}
=======
>>>>>>> fed2135c8e3a1074811af73e598d309ae22480ee
