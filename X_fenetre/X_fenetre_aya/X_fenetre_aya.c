#include <SDL2/SDL.h>
#include <stdio.h>


int main(int argc, char **argv) {
  (void)argc;
  (void)argv;    
  SDL_Window* window[90];          

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", 
    SDL_GetError());               
    exit(EXIT_FAILURE);
  }
  SDL_DisplayMode screen;
  SDL_GetCurrentDisplayMode(0,&screen);

  int k=0;
  int i=0;
  int nbfenetre=30;
  int x=0;
  int y=0;
  int px=screen.w/nbfenetre;
  int py=screen.h/nbfenetre;
  //la diagonale de N
    for(i=0; i<nbfenetre; i++){ 
    window[i] = SDL_CreateWindow(
   "s",                    
    x, y,                                  
    px, py,                              
    SDL_WINDOW_RESIZABLE);                
    if (window == NULL) {
      SDL_Log("Error : SDL window 1 creation - %s\n", 
      SDL_GetError());                
      SDL_Quit();                                
      exit(EXIT_FAILURE);
    }
    x+=px;
    y+=py;
    }
  //les deux cotés de N
  x=0;
  y=0;
  px=screen.w/nbfenetre;
  py=screen.h/nbfenetre;
  for(i=nbfenetre; i<2*nbfenetre; i++){ 
    window[i] = SDL_CreateWindow(
    "Fenetre",                   
    x, y,                                  
    px, py,                             
    SDL_WINDOW_RESIZABLE);               
    if (window[i] == NULL) {
      SDL_Log("Error : SDL window 1 creation - %s\n", 
      SDL_GetError());                
      SDL_Quit();                               
      exit(EXIT_FAILURE);
    }
    y+=py;
  }
  y=0;
  px=screen.w/nbfenetre;
  py=screen.h/nbfenetre;
  x=screen.w-px;
  for(i=2*nbfenetre; i<3*nbfenetre; i++){ 
    window[i] = SDL_CreateWindow(
    "Fenetre",                    
    x, y,                                 
    px, py,                            
    SDL_WINDOW_RESIZABLE);              
    if (window[i] == NULL) {
      SDL_Log("Error : SDL window 1 creation - %s\n", 
      SDL_GetError());                
      SDL_Quit();                               
    }
    y+=py;
  }
    SDL_Delay(20000);
    for(k=0; k<3*nbfenetre; k++){ 
      SDL_DestroyWindow(window[i]);
    }
    SDL_Quit();
    return 0;
  }
