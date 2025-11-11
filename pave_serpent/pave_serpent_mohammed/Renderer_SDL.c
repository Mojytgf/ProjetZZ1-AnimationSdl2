#include <SDL2/SDL.h>
#include <math.h>

void SDL_ExitWithError(const char *message);

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius);

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Lancement SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("initialisation échouée");

    // Création fenêtre
    window = SDL_CreateWindow("Cercles colorés", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_RESIZABLE);

    if (window == NULL)
        SDL_ExitWithError("creation window échouée");

    // Création renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
        SDL_ExitWithError("creation renderer échouée");

    // Boucle principale
    int quit = 0;
    int centerX = 400;  // Coordonnées du centre du cercle
    int centerY = 300;
    int radius = 200; // Rayon du cercle

    float rotationSpeed = 0.02f; // Vitesse de rotation des cercles
    float angle = 0.0f;          // Angle initial

    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Dessiner les cercles autour du cercle central
        int numCircles = 4;
        float angleStep = 2 * M_PI / numCircles;

        for (int i = 0; i < numCircles; i++)
        {
            // Calculer les coordonnées du cercle
            int circleX = centerX + (int)(radius * cos(angle));
            int circleY = centerY + (int)(radius * sin(angle));

            // Choisir la couleur en fonction de l'index
            SDL_Color color;
            switch (i)
            {
                case 0:
                    color.r = 0;
                    color.g = 0;
                    color.b = 255; // Bleu
                    break;
                case 1:
                    color.r = 255;
                    color.g = 255;
                    color.b = 0; // Jaune
                    break;
                case 2:
                    color.r = 255;
                    color.g = 0;
                    color.b = 0; // Rouge
                    break;
                case 3:
                    color.r = 0;
                    color.g = 255;
                    color.b = 0; // Vert
                    break;
            }

            // Dessiner le cercle
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
            drawCircle(renderer, circleX, circleY, 50);

            // Mettre à jour l'angle
            angle += angleStep;
        }

        // Mettre à jour l'angle de rotation
        angle += rotationSpeed;

        // Afficher le rendu à l'écran
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("Error: %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius)
{
    for (int x = -radius; x <= radius; x++)
    {
        int height = (int)sqrt(radius * radius - x * x);

        for (int y = -height; y <= height; y++)
        {
            SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        }
    }
}
