#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "graphe.h"
#include "recuit_simule.h"



void generateRandomPositions(Node nodes[MATRIX_SIZE]) {
    srand(time(NULL)); // Initialisation de la graine du générateur de nombres aléatoires
    for (int i = 0; i < MATRIX_SIZE; i++) {
        nodes[i].x = rand() % WINDOW_WIDTH;
        nodes[i].y = rand() % WINDOW_HEIGHT;
    }
}

void intialiser_matrice(int matrice[MATRIX_SIZE][MATRIX_SIZE]) {
    for(int i = 0; i < MATRIX_SIZE - 1; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i == j) matrice[i][j] = 0;
            else {
                matrice[i][j] = 1;
                matrice[j][i] = 1;
            }
        }
    }
}

void calculateDistances(Node nodes[MATRIX_SIZE], int matrice[MATRIX_SIZE][MATRIX_SIZE], double distances[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = i + 1; j < MATRIX_SIZE; j++) {
            if (matrice[i][j] == 1) {
                int x1 = nodes[i].x;
                int y1 = nodes[i].y;
                int x2 = nodes[j].x;
                int y2 = nodes[j].y;
                double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                distances[i][j] = distance;
                distances[j][i] = distance;
            }
        }
    }
}

int calculateObjectiveValue(double distances[MATRIX_SIZE][MATRIX_SIZE], int solution[MATRIX_SIZE]) {
    int totaldistance = 0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        int x = solution[i], y = solution[(i + 1) % MATRIX_SIZE];
        totaldistance += distances[x][y];
    }
    totaldistance += distances[0][MATRIX_SIZE - 1];
    return totaldistance;
}

int factorial(int x)
{
    if(x==0) return 1;
    else return x*factorial(x-1);
}

bool checkCollision(Node nodes[MATRIX_SIZE], int index, int x, int y) {
    // Vérifie s'il y a une collision avec un autre sommet
    for (int i = 0; i < index; i++) {
        int dx = nodes[i].x - x;
        int dy = nodes[i].y - y;
        int distanceSquared = dx * dx + dy * dy;
        int minDistanceSquared = (2 * NODE_RADIUS) * (2 * NODE_RADIUS);
        if (distanceSquared < minDistanceSquared) {
            return true; // Collision détectée
        }
    }
    return false; // Aucune collision détectée
}

void generateRandomGraph(int matrice[MATRIX_SIZE][MATRIX_SIZE], float p, Node nodes[MATRIX_SIZE]) {
    srand(time(NULL));

    // Générer des positions aléatoires pour les sommets en évitant les collisions
    for (int i = 0; i < MATRIX_SIZE; i++) {
        bool collision = true;
        while (collision) {
            int x = rand() % (WINDOW_WIDTH - 2 * NODE_RADIUS) + NODE_RADIUS;
            int y = rand() % (WINDOW_HEIGHT - 2 * NODE_RADIUS) + NODE_RADIUS;
            collision = checkCollision(nodes, i, x, y);
            if (!collision) {
                nodes[i].x = x;
                nodes[i].y = y;
            }
        }
    }
    
    // Générer les arêtes du graphe en fonction de la densité de probabilité
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = i + 1; j < MATRIX_SIZE; j++) {
            if ((float)rand() / RAND_MAX <= p) {
                matrice[i][j] = 1;
                matrice[j][i] = 1;
            }
        }
    }
}



void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}

void SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            if (dx * dx + dy * dy <= radius * radius) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}


void drawCircle(SDL_Renderer* renderer, int nodeIndex, TTF_Font* font, Node nodes[MATRIX_SIZE], double distances[MATRIX_SIZE][MATRIX_SIZE], int matrice[MATRIX_SIZE][MATRIX_SIZE]) {
    // Dessiner le disque rempli en noir
    for (int i = 0; i < MATRIX_SIZE; i++) {
        if (i == nodeIndex)
            continue;

        if (matrice[nodeIndex][i] == 1) {
            int x1 = nodes[nodeIndex].x;
            int y1 = nodes[nodeIndex].y;
            int x2 = nodes[i].x;
            int y2 = nodes[i].y;
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

            // Dessiner la distance entre les sommets reliés
            double distance = distances[nodeIndex][i];
            char label[10];
            snprintf(label, sizeof(label), "%.2f", distance);
            SDL_Color color = { 231, 0, 0, 255 };
            SDL_Surface* surface = TTF_RenderText_Solid(font, label, color);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

            int textWidth = surface->w;
            int textHeight = surface->h;
            int textX = (x1 + x2) / 2 - textWidth / 2;
            int textY = (y1 + y2) / 2 - textHeight / 2;

            SDL_Rect textRect = { textX, textY, textWidth, textHeight };
            SDL_RenderCopy(renderer, texture, NULL, &textRect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }   
}
void drawCircle2(SDL_Renderer* renderer, int x, int y, int radius, int nodeIndex, TTF_Font* font, Node nodes[MATRIX_SIZE]) {
    
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    int cols = 0;
    if (nodes[nodeIndex].couleur == 'R') cols = 231;
    
    SDL_SetRenderDrawColor(renderer, 0,cols,0,255);
    SDL_Rect rect;
    rect.x = x - radius;
    rect.y = y - radius;
    rect.w = 2 * radius;
    rect.h = 2 * radius;
    SDL_RenderFillRect(renderer, &rect);
    
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    // Dessiner le numéro du sommet
    char label[10];
    snprintf(label, sizeof(label), "%d", nodeIndex);

    SDL_Texture* texture;
    get_text_and_rect(renderer, x, y, label, font, &texture, &rect);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}


void drawGraph(SDL_Renderer* renderer, int matrice[MATRIX_SIZE][MATRIX_SIZE], Node nodes[MATRIX_SIZE], double distances[MATRIX_SIZE][MATRIX_SIZE], TTF_Font* font) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Dessiner les nœuds et les numéros
    for (int i = 0; i < MATRIX_SIZE; i++) {
        drawCircle(renderer, i, font, nodes, distances, matrice);
    }
    for (int i = 0; i < MATRIX_SIZE; i++) {
        int x = nodes[i].x;
        int y = nodes[i].y;
        drawCircle2(renderer, x, y, NODE_RADIUS, i, font, nodes);
    }

    SDL_RenderPresent(renderer);
}
int Is_Any_Node_Near(Node nodes[MATRIX_SIZE] ,int x,int y)
{
    int j = -1;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        if( (x- nodes[i].x)*(x- nodes[i].x) + (y- nodes[i].y)*(y- nodes[i].y) < NODE_RADIUS*NODE_RADIUS) {
            j = i;
        }
    }
    return j;
}

int compareDistancePaths(int chemin[MATRIX_SIZE], double distances[MATRIX_SIZE][MATRIX_SIZE])
{
    int x,y, distance = 0;
    for (int i=0;i<MATRIX_SIZE-1;i++)
    {
        x = chemin[i];
        y=chemin[i+1];
        distance = distance + distances[x][y];
    }
    x = chemin[0];
    y=chemin[MATRIX_SIZE-1];
    distance = distance + distances[x][y];
    return distance;
}



