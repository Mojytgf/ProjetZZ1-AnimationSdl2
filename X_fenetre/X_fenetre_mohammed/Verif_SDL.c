 
#include <SDL2/SDL.h>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define NUM_WINDOWS 5




int main(int argc, char * argv[])
{
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre principale
    SDL_Window* window = SDL_CreateWindow("Fenêtres en forme de Z",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        return 1;
    }

    // Calcul des dimensions des sous-fenêtres
    int subWindowWidth = WINDOW_WIDTH / NUM_WINDOWS;
    int subWindowHeight = WINDOW_HEIGHT / NUM_WINDOWS;

    // Création des fenêtres sur la première ligne
    for (int i = 0; i < NUM_WINDOWS; i++) {
        SDL_Window* subWindow = SDL_CreateWindow("Fenêtre",
                                                 i* subWindowWidth, 0,
                                                 subWindowWidth, subWindowHeight,
                                                 SDL_WINDOW_SHOWN);
        if (subWindow == NULL) {
            printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
            break;
        }
    }

    // Création des fenêtres sur la dernière ligne
    for (int i = 0; i < NUM_WINDOWS; i++) {
        SDL_Window* subWindow = SDL_CreateWindow("Fenêtre",
                                                 i * subWindowWidth, WINDOW_HEIGHT - subWindowHeight,
                                                 subWindowWidth, subWindowHeight,
                                                 SDL_WINDOW_SHOWN);
        if (subWindow == NULL) {
            printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
            break;
        }
    }

    // Création des fenêtres sur la diagonale
    int diagonalWindowWidth = NUM_WINDOWS * subWindowWidth;
    int diagonalWindowHeight = NUM_WINDOWS * subWindowHeight;
    int diagonalX = (NUM_WINDOWS-1) * subWindowWidth;
    int diagonalY = WINDOW_HEIGHT - diagonalWindowHeight;

    for (int i = 0; i < NUM_WINDOWS; i++) {
        SDL_Window* subWindow = SDL_CreateWindow("Fenêtre",
                                                 diagonalX, diagonalY,
                                                 subWindowWidth, subWindowHeight,
                                                 SDL_WINDOW_SHOWN);
        if (subWindow == NULL) {
            printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
            break;
        }

        diagonalX -= subWindowWidth;
        diagonalY += subWindowHeight;
    }

   SDL_Delay(5000);                           // Pause exprimée  en ms

    // Boucle principale
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }

     

    // Libérer les ressources et quitter SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

   return EXIT_SUCCESS;
}



