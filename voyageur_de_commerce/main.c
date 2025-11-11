#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "methode_de_fourmie.h"
#include "graphe.h"
#include "recuit_simule.h"

int main ()
{

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;
    TTF_Font* fontmessage = NULL;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Échec de l'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Graphe en SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Échec de la création de la fenêtre : %s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Échec de la création du rendu : %s\n", SDL_GetError());
        return -1;
    }

    if (TTF_Init() == -1) {
        printf("Échec de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        return -1;
    }

    font = TTF_OpenFont("arial.ttf", FONT_SIZE);
    if (font == NULL) {
        printf("Échec du chargement de la police de caractères : %s\n", TTF_GetError());
        return -1;
    }

    fontmessage = TTF_OpenFont("game_over.ttf", 70);
    if (fontmessage == NULL) {
        printf("Échec du chargement de la police de caractères : %s\n", TTF_GetError());
        return -1;
    }


    

    int matrice[MATRIX_SIZE][MATRIX_SIZE] = { 0 };
    //initialiser
    Node nodes[MATRIX_SIZE];
    double distances[MATRIX_SIZE][MATRIX_SIZE] = { 0 };

    generateRandomPositions(nodes);

    // Générer un graphe aléatoire
    // double p = 1;
    intialiser_matrice(matrice);
  
    // generateRandomGraph(matrice, p, nodes);

    // exemple de solution optimal
    double pheromones[MATRIX_SIZE][MATRIX_SIZE];
    initializePheromoneMatrix(pheromones);

    

    // Calculer les distances entre les sommets
    calculateDistances(nodes, matrice, distances);
    
    // best solution 
    int bestSolution[MATRIX_SIZE] = {0};


    int S = antColonyOptimization(pheromones, distances,bestSolution);
    printf("la longueur du chemin optimale pour la méthode du fourmie: %d\n",S);

    double initialTemperature = 100.0;
    double coolingRate = 0.95;
    int numIterations = 5000;

    simulatedAnnealing(initialTemperature, coolingRate, numIterations, distances);

    int quit = 0;
    SDL_Event event;
    int verif[MATRIX_SIZE];
    int i = 0;
     
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){

                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    int j = Is_Any_Node_Near(nodes ,mouseX,mouseY);
                    nodes[j].couleur = 'R';
                    if (nodes[j].couleur == 'R' && j!=-1) verif[i] = j;
                        // printf("%d\n",j);
                    //}
                    i++;
                    // Utiliser les coordonnées de la souris (mouseX, mouseY)
                  
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        drawGraph(renderer, matrice, nodes, distances, font);

        bool allNodesColored = true;
        for (int i = 0; i < MATRIX_SIZE; i++) {
        if (nodes[i].couleur != 'R') {
            allNodesColored = false;
            break;
        }
        }

        if (allNodesColored) {
            if (compareDistancePaths(verif, distances) <= S) {
            SDL_Window* messageWindow = SDL_CreateWindow("Résultat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 200, SDL_WINDOW_SHOWN);
            SDL_Renderer* messageRenderer = SDL_CreateRenderer(messageWindow, -1, SDL_RENDERER_ACCELERATED);

            SDL_SetRenderDrawColor(messageRenderer, 255, 255, 255, 255);
            SDL_RenderClear(messageRenderer);

            SDL_Color textColor = {0, 0, 0, 0};
            SDL_Surface* surface = TTF_RenderText_Solid(fontmessage, "Congratulation !", textColor);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(messageRenderer, surface);
            int textWidth = surface->w;
            int textHeight = surface->h;
            SDL_Rect textRect = {200 - textWidth / 2, 100 - textHeight / 2, textWidth, textHeight};
            SDL_RenderCopy(messageRenderer, texture, NULL, &textRect);
            SDL_RenderPresent(messageRenderer);

            SDL_Delay(3000);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
            SDL_DestroyRenderer(messageRenderer);
            SDL_DestroyWindow(messageWindow);

            quit = 1; // Quitter la boucle principale
        } else {
            SDL_Window* messageWindow = SDL_CreateWindow("Résultat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 200, SDL_WINDOW_SHOWN);
            SDL_Renderer* messageRenderer = SDL_CreateRenderer(messageWindow, -1, SDL_RENDERER_ACCELERATED);

            SDL_SetRenderDrawColor(messageRenderer, 255, 255, 255, 255);
            SDL_RenderClear(messageRenderer);

            SDL_Color textColor = {0, 0, 0, 0};
            SDL_Surface* surface = TTF_RenderText_Solid(fontmessage, "Game Over !", textColor);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(messageRenderer, surface);
            int textWidth = surface->w;
            int textHeight = surface->h;
            SDL_Rect textRect = {200 - textWidth / 2, 100 - textHeight / 2, textWidth, textHeight};
            SDL_RenderCopy(messageRenderer, texture, NULL, &textRect);
            SDL_RenderPresent(messageRenderer);

            SDL_Delay(2500);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
            SDL_DestroyRenderer(messageRenderer);
            SDL_DestroyWindow(messageWindow);

            quit = 1; // Quitter la boucle principale
        }
    }

        SDL_RenderPresent(renderer);
    }
    
    // for (int i = 0; i<MATRIX_SIZE; i++)
    // {
    //      if (i == MATRIX_SIZE-1) printf("%d\n",verif[i]);
    //      else printf("%d\t",verif[i]);
    //  }
 
    printf("la longueur du chemin choisi :%d\n",compareDistancePaths(verif,distances));
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}