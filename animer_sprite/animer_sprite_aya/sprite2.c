#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>

const int LARGEUR = 800;
const int HAUTEUR = 600;

void animate_sprite_and_background(SDL_Texture* textureFond, SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer) {
    int positionFondX = 0;
    int positionSpriteX = 0;

    SDL_Rect 
           source = {0},                    
           window_dimensions = {0};        
                        

    int vitesseFond = 2;
    int vitesseSprite = 4;

    SDL_Event evenement;
    int continuer = 1;

    int offset_x = 0; 
    int offset_y = 0; 
    int nb_images = 0; 
    float zoom = 0; 

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

    nb_images = 8; 
    zoom = 4; 

    offset_x = source.w / 13; 
    offset_y = source.h / 8; 

    SDL_Rect state = {0, 3* offset_y, offset_x, offset_y};

    while (continuer) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) {
                continuer = 0;
            }
        }

        positionFondX += vitesseFond;
        if (positionFondX >= LARGEUR) {
            positionFondX = 0;
        }

        positionSpriteX += vitesseSprite;
        if (positionSpriteX >= LARGEUR) {
            positionSpriteX = 0;
        }

        SDL_RenderClear(renderer);

        SDL_Rect fondRect1 = {positionFondX, 0, LARGEUR, HAUTEUR};
        SDL_Rect fondRect2 = {positionFondX - LARGEUR, 0, LARGEUR, HAUTEUR};

        SDL_RenderCopy(renderer, textureFond, NULL, &fondRect1);
        SDL_RenderCopy(renderer, textureFond, NULL, &fondRect2);

        SDL_Rect spriteRect = {positionSpriteX, (HAUTEUR - offset_y * zoom) / 2, offset_x * zoom, offset_y * zoom};
        SDL_RenderCopy(renderer, my_texture, &state, &spriteRect);

        SDL_RenderPresent(renderer);

        SDL_Delay(80);

        state.x += offset_x;
        state.x %= offset_x * nb_images;
    }
}


int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Échec de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* fenetre = SDL_CreateWindow("Animation avec SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (fenetre == NULL) {
        printf("Échec de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (rendu == NULL) {
        printf("Échec de la création du rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface1 = IMG_Load("A.png");
    if (surface1 == NULL) {
        printf("Échec du chargement de l'image du sprite : %s\n", SDL_GetError());
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texturesprite = SDL_CreateTextureFromSurface(rendu, surface1);
    SDL_FreeSurface(surface1);
    if (texturesprite == NULL) {
        printf("Échec de la création de la texture du sprite : %s\n", SDL_GetError());
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surfaceFond = IMG_Load("background.jpg");
    if (surfaceFond == NULL) {
        printf("Échec du chargement de l'image de l'arrière-plan : %s\n", SDL_GetError());
        SDL_DestroyTexture(texturesprite);
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* textureFond = SDL_CreateTextureFromSurface(rendu, surfaceFond);
    SDL_FreeSurface(surfaceFond);
    if (textureFond == NULL) {
        printf("Échec de la création de la texture de l'arrière-plan : %s\n", SDL_GetError());
        SDL_DestroyTexture(texturesprite);
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    animate_sprite_and_background(textureFond, texturesprite, fenetre, rendu);

    SDL_DestroyTexture(texturesprite);
    SDL_DestroyTexture(textureFond);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}