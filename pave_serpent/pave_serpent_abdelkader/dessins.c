#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    

    int WINDOW_WIDTH = 500;
    int WINDOW_HEIGHT = 400;
    int STAR_SIZE = 70;
    int STAR_SPEED = 6;


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Bouncing Star", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }


    SDL_Rect star;
    star.w = STAR_SIZE;
    star.h = STAR_SIZE;
    star.x = (WINDOW_WIDTH - star.w) / 2;
    star.y = (WINDOW_HEIGHT - star.h) / 2;
    int dx = STAR_SPEED;
    int dy = STAR_SPEED;

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        star.x += dx;
        star.y += dy;
//closition detection des murs ou (bounds)
        if (star.x <= 0 || star.x >= WINDOW_WIDTH - star.w) {
            dx = -dx;
        }
        if (star.y <= 0 || star.y >= WINDOW_HEIGHT - star.h) {
            dy = -dy;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &star);

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
