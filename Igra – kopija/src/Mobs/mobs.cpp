#include "mobs.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <time.h>
#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720

    
SDL_Window *globalWindow; //* globalna spremenljivka za window
SDL_Renderer *globalRenderer; //* globalna spremenljivka za renderer


Player:: Player() { 
    x=500;
    y=500;
    radius=60;
}

bool Player:: Borders(int minX, int maxX, int minY, int maxY)  { //* metoda za omejevanje premikov
            //* window borderji
                if (x>=maxX){
                    x=maxX-(x-maxX);
                }
                if(x<=minX) {
                    x=minX-x;
                }
                if (y>=maxY){
                  y=maxY-(y-maxY);
                }
                if(y<=minY) {
                    y=minY-y;
                }
            //*borderji za ta dvignjen platform ( kjer greš lahko gor po stopnicah)
                //* vse levo od stopnic
                if ((x>=550 && x<600)&&(y>=275&&y<=325)){
                    y=325+25;
                }
                if ((x>=525 && x<550)&&(y>=250&&y<=300)){
                    y=300;//* tuki ni +25 ker zgleda lepš
                }
                if ((x>=500 && x<550)&&(y>=250&&y<=275)){
                    y=250+25;
                }
                if ((x>=425 && x<550)&&(y>=200&&y<=275)){
                    y=275+25;
                }
                 if ((x>=400 && x<425)&&(y>=200&&y<=225)){
                    y=225;
                }
                if ((x>=325 && x<400)&&(y>=150&&y<=225)){
                    y=225;
                }
                if ((x>=275 && x<325)&&(y>=125&&y<=175)){
                    y=175;
                }
                if ((x>=175 && x<275)&&(y>=125&&y<=175)){
                    y=175;
                }
                if ((x>=75 && x<175)&&(y>=125&&y<=175)){
                    y=200;
                }
                if ((x>=0 && x<75)&&(y>=100&&y<=150)){
                    y=150;
                }
            //* vse desno od 1.stopnic
                if ((x>=650 && x<750)&&(y>=275&&y<=350)){
                    y=350;
                }
                if ((x>=750 && x<775)&&(y>=250&&y<=300)){
                    y=300;
                }
                 if ((x>=775 && x<850)&&(y>=225&&y<=275)){
                    y=275;
                }
                 if ((x>=825 && x<850)&&(y>=250&&y<=300)){
                    y=300;
                }
                 if ((x>=850 && x<875)&&(y>=275&&y<=325)){
                    y=325;
                }
                 if ((x>=875 && x<950)&&(y>=300&&y<=350)){
                    y=350;
                }
                 if ((x>=975 && x<1050)&&(y>=300&&y<=350)){ //* desno od stopnic
                    y=350;
                }
                   if ((x>=1025 && x<1075)&&(y>=225&&y<=300)){
                    y=300;
                }
                if ((x>=1025 && x<1050)&&(y>=75&&y<=200)){
                    x+=25; //* tuki lik proba it cez border z desne,zato ga ko prečka border samo pomaknemo v dovoljen prostor
                }
                if ((x>=1050 && x<1150)&&(y>=50&&y<=100)){
                    y=100;
                }
                if ((x>=1150 && x<1175)&&(y>=50&&y<=125)){
                    x-=25; //* tuki lik proba it cez border z leve,zato ga ko prečka border samo pomaknemo v dovoljen prostor
                }
                if ((x>=1125 && x<1250)&&(y>=75&&y<=150)){
                    y=150;
                } 

               
                

        return (x >= minX && x <= maxX && y >= minY && y <= maxY);
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
const int movementSpeed = 25;
  //* Spodaj beremo input s tipkovnice nato pa premaknemo Player-ja za 25px v neko smer
    
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
    SDL_FreeSurface(mcSurface);
    SDL_RenderCopy(globalRenderer, mc, NULL, &mcDst);
    SDL_RenderPresent(globalRenderer); //* outputa/nariše na screen sliko  (SAMO PR OBJEKTU KI SE ZADNJI RENDERA MEJ TO)
    std::cout<<x<<y<<std::endl;
}


Baraba::Baraba() {
    srand(time(NULL));

    for (int i = 0; i < 5; ++i) {
        Baraba bar;
        bar.x = 1000;
        bar.y = 500;
        bar.radius = 60;

        vectBar.push_back(bar);
    }
}
void Baraba:: Borders(int minX, int maxX, int minY, int maxY)  { //* metoda za omejevanje premikov
            //* window borderji
                if (x>=maxX){
                    x=maxX-(x-maxX);
                }
                if(x<=minX) {
                    x=minX-x;
                }
                if (y>=maxY){
                  y=maxY-(y-maxY);
                }
                if(y<=minY) {
                    y=minY-y;
                }
            //*borderji za ta dvignjen platform ( kjer greš lahko gor po stopnicah)
                //* vse levo od stopnic
                if ((x>=550 && x<600)&&(y>=275&&y<=325)){
                    y=325+25;
                }
                if ((x>=525 && x<550)&&(y>=250&&y<=300)){
                    y=300;//* tuki ni +25 ker zgleda lepš
                }
                if ((x>=500 && x<550)&&(y>=250&&y<=275)){
                    y=250+25;
                }
                if ((x>=425 && x<550)&&(y>=200&&y<=275)){
                    y=275+25;
                }
                 if ((x>=400 && x<425)&&(y>=200&&y<=225)){
                    y=225;
                }
                if ((x>=325 && x<400)&&(y>=150&&y<=225)){
                    y=225;
                }
                if ((x>=275 && x<325)&&(y>=125&&y<=175)){
                    y=175;
                }
                if ((x>=175 && x<275)&&(y>=125&&y<=175)){
                    y=175;
                }
                if ((x>=75 && x<175)&&(y>=125&&y<=175)){
                    y=200;
                }
                if ((x>=0 && x<75)&&(y>=100&&y<=150)){
                    y=150;
                }
            //* vse desno od 1.stopnic
                if ((x>=650 && x<750)&&(y>=275&&y<=350)){
                    y=350;
                }
                if ((x>=750 && x<775)&&(y>=250&&y<=300)){
                    y=300;
                }
                 if ((x>=775 && x<850)&&(y>=225&&y<=275)){
                    y=275;
                }
                 if ((x>=825 && x<850)&&(y>=250&&y<=300)){
                    y=300;
                }
                 if ((x>=850 && x<875)&&(y>=275&&y<=325)){
                    y=325;
                }
                 if ((x>=875 && x<950)&&(y>=300&&y<=350)){
                    y=350;
                }
                 if ((x>=975 && x<1050)&&(y>=300&&y<=350)){ //* desno od stopnic
                    y=350;
                }
                   if ((x>=1025 && x<1075)&&(y>=225&&y<=300)){
                    y=300;
                }
                if ((x>=1025 && x<1050)&&(y>=75&&y<=200)){
                    x+=25; //* tuki lik proba it cez border z desne,zato ga ko prečka border samo pomaknemo v dovoljen prostor
                }
                if ((x>=1050 && x<1150)&&(y>=50&&y<=100)){
                    y=100;
                }
                if ((x>=1150 && x<1175)&&(y>=50&&y<=125)){
                    x-=25; //* tuki lik proba it cez border z leve,zato ga ko prečka border samo pomaknemo v dovoljen prostor
                }
                if ((x>=1125 && x<1250)&&(y>=75&&y<=150)){
                    y=150;
                } 

        return;
    }

void Baraba:: Render () {
     SDL_Surface *barSurface=IMG_Load("assets/baddie.png");
    if(!barSurface){
         printf("Error: Failed to load player image\nSDL_Image Error: '%s'\n", IMG_GetError());        
    } 
    
    SDL_Texture *bar = SDL_CreateTextureFromSurface(globalRenderer , barSurface);
    if(!bar){
        printf("Error: Failed to create texture\n");     
    }

    SDL_Rect barDst = {
        .x = x, //* na katerem x-u bos postavu sliko
        .y = y, //* na keretem y-u bos postavu sliko
        .w = 50, //* širina slike, ki jo bomo dodali                      
        .h = 50,                      
    };
const int movementSpeed = 25;
//* Spodaj beremo input s tipkovnice nato pa premaknemo Player-ja za 25px v neko smer
    
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
    SDL_FreeSurface(barSurface);
    SDL_RenderCopy(globalRenderer, bar, NULL, &barDst);
    SDL_DestroyTexture(bar);
}





void Back:: Start(){
    //* SDL_window je samo nov tab, ki se odpre
        globalWindow = SDL_CreateWindow("DELA <3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
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
}
