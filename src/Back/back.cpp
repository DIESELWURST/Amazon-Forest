#include "back.hpp"
#include <SDL2/SDL_image.h>

extern SDL_Window *globalWindow; //* globalna spremenljivka za window
extern SDL_Renderer *globalRenderer; //* globalna spremenljivka za renderer
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

void Back:: Start(){
    //* SDL_window je samo nov tab, ki se odpre
        globalWindow = SDL_CreateWindow("Blaze Busters: Amazon Rescue", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!globalWindow){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
       
    }
    //*SDL_Renderer je pa dobesedno plac na katerega bomo risal
        globalRenderer = SDL_CreateRenderer(globalWindow, -1, SDL_RENDERER_ACCELERATED );
    if(!globalRenderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
    }  
}
void Back:: Render() {
           //* surface samo predstavlja sliko v pomnilniku
    SDL_Surface *backingSurface = IMG_Load("assets/back.png");
    if(!backingSurface){
        printf("Error: Failed to load image\nSDL_Image Error: '%s'\n", IMG_GetError());
    }

    //* texture je samo bolj optimiziran surface ( render in surface v enem)
    SDL_Texture *backing = SDL_CreateTextureFromSurface(globalRenderer, backingSurface);
    if(!backing){
        printf("Error: Failed to create texture\n");      
    }

    //* samo deklariral smo strukturo pravokotnik (rectangle), ki nam pove kje bomo rederal sliko
    SDL_Rect backingDst = {
        .x = 0, //* na katerem x-u bos postavu sliko
        .y = 0, //* na keretem y-u bos postavu sliko
        .w = SCREEN_WIDTH, //* širina slike, ki jo bomo dodali                      
        .h =  SCREEN_HEIGHT,  //* višina slike, ki jo bomo dodali                     
    };

        SDL_FreeSurface(backingSurface);//* sprosti prostor v pomnilniku, ki ga je zasedel surface     
        SDL_SetRenderDrawColor(globalRenderer, 42, 98, 61, 1); //* rederer nastav na barve rgba (r,g,b,a- svetloba)
        SDL_RenderCopy(globalRenderer, backing, NULL, &backingDst);//* samo še enkrat prekopira texture na render   
        SDL_DestroyTexture(backing); 
}
