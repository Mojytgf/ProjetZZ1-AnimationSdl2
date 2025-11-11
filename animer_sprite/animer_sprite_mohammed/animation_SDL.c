#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

#define SPRITE_WIDTH 240
#define SPRITE_HEIGHT 296
#define NUM_SPRITES_PER_ROW 6
#define NUM_SPRITES_PER_COL 5
#define ANIMATION_DELAY 25
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(int argc, char** argv) {
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("SDL2 Sprite Sheets",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Charger les images de fond d'écran
    char backgroundPath[256];
    SDL_Texture* backgroundTextures[48];
    for (int i = 0; i < 48; i++) {
        snprintf(backgroundPath, sizeof(backgroundPath), "./Background/background%d.png", i);
        SDL_Surface* backgroundImage = IMG_Load(backgroundPath);
        backgroundTextures[i] = SDL_CreateTextureFromSurface(renderer, backgroundImage);
        SDL_FreeSurface(backgroundImage);
    }

    // Charger les sprites
    SDL_Surface* spriteImage = IMG_Load("spritesheet.png");
    SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteImage);
    SDL_FreeSurface(spriteImage);

    SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
    SDL_RenderClear(renderer);

    Uint32 prevTime = SDL_GetTicks();
    int currentSprite = 0;
    int currentBackgroundFrame = 0;

    while (!quit) {
        SDL_PollEvent(&event);

        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        }

        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - prevTime;

        if (deltaTime >= ANIMATION_DELAY) {
            currentSprite = (currentSprite + 1) % (NUM_SPRITES_PER_ROW * NUM_SPRITES_PER_COL);
            int spriteRow = currentSprite % NUM_SPRITES_PER_ROW;
            int spriteCol = currentSprite / NUM_SPRITES_PER_ROW;
            int spriteX = (WINDOW_WIDTH - SPRITE_WIDTH) / 2;
            int spriteY = (WINDOW_HEIGHT - SPRITE_HEIGHT) / 2+30;

            SDL_Rect srcrect = { spriteRow * SPRITE_WIDTH, spriteCol * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT };
            SDL_Rect dstrect = { spriteX, spriteY, SPRITE_WIDTH, SPRITE_HEIGHT };

            SDL_RenderClear(renderer);

            // Afficher le fond d'écran
            SDL_Texture* currentBackgroundTexture = backgroundTextures[currentBackgroundFrame];
            SDL_RenderCopy(renderer, currentBackgroundTexture, NULL, NULL);

            // Afficher le sprite
            SDL_RenderCopy(renderer, spriteTexture, &srcrect, &dstrect);
            SDL_RenderPresent(renderer);

            prevTime = currentTime;
            currentBackgroundFrame = (currentBackgroundFrame + 1) % 48;  // Changer le fond d'écran pour le prochain frame
        }
    }

    // Libérer les textures du fond d'écran
    for (int i = 0; i < 48; i++) {
        SDL_DestroyTexture(backgroundTextures[i]);
    }

    SDL_DestroyTexture(spriteTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
