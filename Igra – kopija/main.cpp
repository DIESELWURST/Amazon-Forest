#include "render.hpp"
#include "mobs.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

//* - Razlaga ukazov,funkcij,spremenljivk,pogojev
//  - Razlaga zank,struktur,objektov 
//? -


int main(int argc, char** argv){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){ //* s tem poveš compilerju, da boš začel delat z SDL
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        printf("VSE je fuč");
        return 1;
    }

    Back inititalise;// Razred Back je tu deklariran, saj bo prvi objekt s katerim bomo delali in ga potrebujemo za klic funkcije start
    inititalise.Start();// funkcija start bo deklarirala renderer in odprla okno
// while loop, ki samo preverja, če se je kej zgodil ( tuki posebi gleda če smo zaprl program)
    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }
        
        Render ();

    }

  //  SDL_DestroyTexture(backing);
  //  SDL_DestroyRenderer(globalRenderer);
  //  SDL_DestroyWindow(globalWindow);
    IMG_Quit();

    return 0;
}