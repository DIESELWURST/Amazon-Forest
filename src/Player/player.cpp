#include "player.hpp"
#include "mobs.hpp"
#include <SDL2/SDL_image.h>


extern SDL_Window *globalWindow; //* globalna spremenljivka za window
extern SDL_Renderer *globalRenderer; //* globalna spremenljivka za renderer
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;



Player:: Player() { 
    x=500;
    y=500;
    radius=60;
}



 bool Player:: Borders (int minX, int maxX, int minY, int maxY)  {
    return Mobs::Borders (minX,maxX,minY,maxY);
 }


void Player::Update() {
    const int movementSpeed = 25;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); //* beremo/dobimo stanje tipkovnice
    if (currentKeyStates[SDL_SCANCODE_W])
        y -= movementSpeed;
    if (currentKeyStates[SDL_SCANCODE_A])
        x -= movementSpeed;
    if (currentKeyStates[SDL_SCANCODE_S])
        y += movementSpeed;
    if (currentKeyStates[SDL_SCANCODE_D])
        x += movementSpeed;

    Borders(0, SCREEN_WIDTH - 50, 0, SCREEN_HEIGHT - 50);
}


void Player:: Render() {
    SDL_Surface *mcSurface=IMG_Load("assets/player_front.png");
    if(!mcSurface){
         printf("Error: Failed to load player image\nSDL_Image Error: '%s'\n", IMG_GetError());        
    } 
    
    SDL_Texture *mc = SDL_CreateTextureFromSurface(globalRenderer , mcSurface);
    if(!mc){
        printf("Error: Failed to create texture\n");     
    }
    SDL_Rect mcDst = {
        .x = x, //* na katerem x-u bos postavu sliko
        .y = y, //* na keretem y-u bos postavu sliko
        .w = 50, //* širina slike, ki jo bomo dodali                      
        .h =  50,                      
    };
    SDL_FreeSurface(mcSurface);
    SDL_RenderCopy(globalRenderer, mc, NULL, &mcDst);
    SDL_RenderPresent(globalRenderer); //* outputa/nariše na screen sliko  (SAMO PR OBJEKTU KI SE ZADNJI RENDERA MEJ TO)
    
}

