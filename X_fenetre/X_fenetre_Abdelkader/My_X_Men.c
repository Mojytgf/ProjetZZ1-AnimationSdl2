#include <SDL2/SDL.h>

#define WINDOW_TITLE "SDL2 Window"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    int displayIndex = 0;
    SDL_DisplayMode mode;

    if (SDL_GetCurrentDisplayMode(displayIndex, &mode) != 0) {
        printf("Erreur %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* windowXMEN[120];
    for(int k=0; k<120;k++)
    {
        
        if(k<40)
        { 
            windowXMEN[k] = SDL_CreateWindow("alpha", ((40-k)* mode.w) / 40 , (k* mode.h) / 40, mode.w / 40 , mode.h / 40 , SDL_WINDOW_SHOWN);
            
        }
        else if(k <80)
        {
            windowXMEN[k] = SDL_CreateWindow("alpha", 0 , ((80-k)* mode.h) / 40, mode.w / 40 , mode.h / 40 , SDL_WINDOW_SHOWN);
        }
        if(k>=80)
        {
            windowXMEN[k] = SDL_CreateWindow("alpha",  ((k-80)* mode.w) / 40 , ((k-80)* mode.h) / 40, mode.w / 40 , mode.h / 40 , SDL_WINDOW_SHOWN);
        }

        if (windowXMEN[k] == NULL) 
        {
                printf("Erreur lors de la création de la fenêtre %d : %s\n", k,SDL_GetError());
                SDL_Quit();
                return 1;
        }
    }


    int ProgramON = 1;

    while (ProgramON) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) 
            {
                ProgramON = !ProgramON;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_SPACE:
                        ProgramON = !ProgramON;
                        break;
                    default:
                        break;
                }
            }
            
        }
    }

    for(int k=0; k<120;k++)
    {
        SDL_DestroyWindow(windowXMEN[k]);
    }
    SDL_Quit();

    return 0;
}

