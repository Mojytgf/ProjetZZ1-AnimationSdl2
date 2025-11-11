#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600
#define SPRITE_WIDTH 116
#define SPRITE_HEIGHT 76
#define SPRITES_PER_ROW 4
#define TOTAL_SPRITES 17

// Function to load a texture from file
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* spriteSheet = NULL;

    SDL_Rect spriteClips[TOTAL_SPRITES];
    int currentSprite = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Sprite Animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    spriteSheet = loadTexture(renderer, "css_sprites2.png");
    if (spriteSheet == NULL) {
        printf("Failed to load sprite sheet image! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Set the sprite clips
    for (int i = 0; i < TOTAL_SPRITES; ++i) {
        spriteClips[i].x = (i % SPRITES_PER_ROW) * SPRITE_WIDTH;
        spriteClips[i].y = (i / SPRITES_PER_ROW) * SPRITE_HEIGHT;
        spriteClips[i].w = SPRITE_WIDTH;
        spriteClips[i].h = SPRITE_HEIGHT;
    }

    SDL_Event event;
    int quit = 0;
    int spriteX = 0;
    int spriteY = 0;
    double rotationAngle = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_RenderClear(renderer);

        //SDL_RenderCopyEx(renderer, texture, NULL, &destinationRect, rotationAngle, &center, SDL_FLIP_NONE);

        //SDL_RenderCopy(renderer, spriteSheet, &spriteClips[currentSprite], &destRect);
        
        int Pas_X = (WINDOW_WIDTH - SPRITE_WIDTH) / 40;
        int Pas_Y = (WINDOW_HEIGHT - SPRITE_HEIGHT) / 40;

        // Calculate destination rectangle for rendering the texture as a square inside the box
        SDL_Rect destinationRect = { spriteX, spriteY ,SPRITE_WIDTH,SPRITE_HEIGHT};
/*
        if(destinationRect.x == 0 && spriteY == 0)
        {
            destinationRect.x = BOX_SIZE/2;
            spriteY = BOX_SIZE/2;
        }*/
        
        if(spriteY <= 0 && spriteX + Pas_X < WINDOW_WIDTH - SPRITE_WIDTH*0.8)
        {
            if(spriteX < - SPRITE_WIDTH*0.1) rotationAngle += 90;
            spriteX += Pas_X;
            //printf("AM here");
            if(spriteX + Pas_X >= WINDOW_WIDTH - SPRITE_WIDTH)
            {
                spriteX = WINDOW_WIDTH - SPRITE_WIDTH*0.8;
            }
        }
        //if(spriteX - Pas_X >= WINDOW_WIDTH - BOX_SIZE)  printf("AM here");
        if( spriteX > WINDOW_WIDTH - SPRITE_WIDTH && spriteY + Pas_Y < WINDOW_HEIGHT - SPRITE_HEIGHT)
        {
            if(spriteY == 0) rotationAngle += 90;
            spriteY += Pas_Y;
            //printf("AM here");
            if(spriteY + Pas_Y >= WINDOW_HEIGHT - SPRITE_HEIGHT)
            {
                spriteY = WINDOW_HEIGHT - SPRITE_HEIGHT;
            }
        }
        
        if( spriteY == WINDOW_HEIGHT - SPRITE_HEIGHT && spriteX - Pas_X > 0)
        {
            if(spriteX >= WINDOW_WIDTH - SPRITE_WIDTH*0.9) rotationAngle += 90;
            spriteX -= Pas_X;
            if(spriteX - Pas_X <= 0)
            {
                spriteX = - SPRITE_WIDTH*0.2;
            }
            //printf("AM here");
        }
        if( spriteX < 0 && spriteY - Pas_Y > 0)
        {
            if(spriteY == WINDOW_HEIGHT - SPRITE_HEIGHT) rotationAngle += 90;
            spriteY -= Pas_Y;
            if(spriteY - Pas_Y <= 0)
            {
                spriteY = 0;
            }
            //printf("AM here");
        }
//SPRITE_WIDTH, SPRITE_HEIGHT 



        SDL_Point center;
        center.x = destinationRect.w / 2;
        center.y = destinationRect.h / 2;

        SDL_RenderCopyEx(renderer, spriteSheet, &spriteClips[currentSprite], &destinationRect, rotationAngle, &center, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);

        // Delay to control animation speed
        SDL_Delay(80);

        // Move to the next sprite
        currentSprite = (currentSprite + 1) % TOTAL_SPRITES;
    }

    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
