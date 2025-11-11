#ifndef GRAPHE
#define GRAPHE

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


#define MATRIX_SIZE 6
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define NODE_RADIUS 20
#define FONT_SIZE 12


typedef struct {
    int x;
    int y;
    char couleur;
} Node;

void generateRandomPositions(Node nodes[MATRIX_SIZE]);

void intialiser_matrice(int matrice[MATRIX_SIZE][MATRIX_SIZE]);

void calculateDistances(Node nodes[MATRIX_SIZE], int matrice[MATRIX_SIZE][MATRIX_SIZE], double distances[MATRIX_SIZE][MATRIX_SIZE]);

int calculateObjectiveValue(double distances[MATRIX_SIZE][MATRIX_SIZE] ,int solution[MATRIX_SIZE]);

int factorial(int x);

bool checkCollision(Node nodes[MATRIX_SIZE], int index, int x, int y);

void generateRandomGraph(int matrice[MATRIX_SIZE][MATRIX_SIZE], float p, Node nodes[MATRIX_SIZE]) ;

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect);

void SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius) ;

void drawCircle(SDL_Renderer* renderer, int nodeIndex, TTF_Font* font, Node nodes[MATRIX_SIZE], double distances[MATRIX_SIZE][MATRIX_SIZE], int matrice[MATRIX_SIZE][MATRIX_SIZE]); 

void drawCircle2(SDL_Renderer* renderer, int x, int y, int radius, int nodeIndex, TTF_Font* font, Node nodes[MATRIX_SIZE]) ;

void drawGraph(SDL_Renderer* renderer, int matrice[MATRIX_SIZE][MATRIX_SIZE], Node nodes[MATRIX_SIZE], double distances[MATRIX_SIZE][MATRIX_SIZE], TTF_Font* font) ;

int Is_Any_Node_Near(Node nodes[MATRIX_SIZE] ,int x,int y);

int compareDistancePaths(int chemin[MATRIX_SIZE], double distances[MATRIX_SIZE][MATRIX_SIZE]);

#endif