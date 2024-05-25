#include "menu.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern SDL_Window *globalWindow; //* globalna spremenljivka za window + vse extern spremenljivke so v datoteki globals
extern SDL_Renderer *globalRenderer; //* globalna spremenljivka za renderer
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

int Menu::init() {
    // Nalaganje slike menija
    SDL_Surface *menuSurface = IMG_Load("assets/menu.png");
    if (!menuSurface) {
        printf("Error: Failed to load image\nSDL_Image Error: '%s'\n", IMG_GetError());
        return -1; // Dodana vrnjena vrednost v primeru napake pri nalaganju slike
    }

    // Ustvarjanje teksture menija
    SDL_Texture *menuTexture = SDL_CreateTextureFromSurface(globalRenderer, menuSurface);
    if (!menuTexture) {
        printf("Error: Failed to create texture\n");
        SDL_FreeSurface(menuSurface);
        return -1; // Dodana vrnjena vrednost v primeru napake pri ustvarjanju teksture
    }

    // Ustvarjanje pravokotnika za renderiranje menija
    SDL_Rect menuDst = { 
        .x = 0,
        .y = 0, 
        .w = SCREEN_WIDTH, 
        .h = SCREEN_HEIGHT
        };

    // Prikaz slike menija na zaslonu
    SDL_RenderCopy(globalRenderer, menuTexture, NULL, &menuDst);
    SDL_RenderPresent(globalRenderer);

    // Sprostitev uporabljenih virov
    SDL_FreeSurface(menuSurface);
    SDL_DestroyTexture(menuTexture);
    // Zanka za čakanje na pritisk tipke
    SDL_Event event;
    int mode = 0;
    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_1:
                        mode = 1;
                        break;
                    case SDL_SCANCODE_2:
                        mode = 2;
                        break;
                    case SDL_SCANCODE_3:
                        mode = 3;
                        break;
                    case SDL_SCANCODE_4:
                        mode = 4;
                        break;
                    default:
                        break;
                }
                break; // Izhod iz zanke, ko je pritisnjena tipka
            }
        }
        SDL_Delay(100); // Dodan delay, da se zmanjša obremenitev procesorja
    }

    return mode;
}