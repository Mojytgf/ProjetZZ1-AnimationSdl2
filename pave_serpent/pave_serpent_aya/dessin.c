#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

 int main(){ 
  SDL_Window* window = NULL;            
  SDL_Renderer* renderer = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", 
    SDL_GetError());                
    exit(EXIT_FAILURE);
  }
  window = SDL_CreateWindow("fenetre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
  if(window == NULL){
    printf("Erreur lors de la création de la fenetre: %s\n", SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(renderer == NULL){
    printf("Erreur lors de la création du rendu: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_FAILURE;
  }

int triangleSize = 100;
int triangleHeight = (int)(triangleSize * sqrt(3)/2);
int triangleTopX = (800 - triangleSize)/2;
int triangleTopY = (600 - triangleHeight)/2;
int triangleLeftX = triangleTopX;
int triangleLeftY = triangleTopY + triangleHeight;
int triangleRightX = triangleTopX + triangleSize;
int triangleRightY = triangleTopY + triangleHeight;
int triangleSpeed = 2; 
int quit = 0;
SDL_Event event;
while(!quit){
        SDL_PollEvent(&event);

        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        }
    triangleTopX += triangleSpeed;
    triangleLeftX += triangleSpeed;
    triangleRightX += triangleSpeed;
    if(triangleTopX <=0 || triangleRightX >=800){
        triangleSpeed = -triangleSpeed;
    }


  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawLine(renderer, triangleLeftX, triangleLeftY, triangleRightX, triangleRightY);
  SDL_RenderDrawLine(renderer, triangleRightX, triangleRightY, triangleTopX, triangleTopY);
  SDL_RenderDrawLine(renderer, triangleTopX, triangleTopY, triangleLeftX, triangleLeftY);


  SDL_RenderPresent(renderer);
  SDL_Delay(10);
}
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}