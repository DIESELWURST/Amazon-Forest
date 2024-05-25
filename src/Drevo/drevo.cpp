#include "drevo.hpp"
#include <SDL2/SDL_image.h>

extern SDL_Renderer *globalRenderer; //* globalna spremenljivka za renderer
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
void Drevo:: fillDrev(std::vector<Drevo>&vectDrev){
    
   for(int i=0;i<vectDrev.size();i++){
        if(i==0){
            vectDrev[i].x=0;
            vectDrev[i].y=300;
        } else if (i==1){
            vectDrev[i].x=145;
            vectDrev[i].y=255;
        } else if (i==2){
          vectDrev[i].x=273;
          vectDrev[i].y=527;  
        } else if (i==3){
            vectDrev[i].x=700;
            vectDrev[i].y=500; 
        } else if (i==4){
            vectDrev[i].x=675;
            vectDrev[i].y=250; 
        } else if (i==5){
            vectDrev[i].x=1075;
            vectDrev[i].y=300; 
        } else if (i==6){
            vectDrev[i].x=1175;
            vectDrev[i].y=550; 
        } else if (i==7){
            vectDrev[i].x=1210;
            vectDrev[i].y=200; 
        }
        vectDrev[i].je_posekan=false;
   }

 }
 
    void Drevo::Render(int i) {
    if (!je_posekan) return;

    const char * fileNames[] = {
        "assets/drevo1.png",
        "assets/drevo2.png",
        "assets/drevo3.png",
        "assets/drevo4.png",
        "assets/drevo5.png",
        "assets/drevo6.png",
        "assets/drevo7.png",
        "assets/drevo8.png"
    };

    SDL_Rect sizes[] = {
        {x, y, 125, 256},
        {x, y, 201, 180},
        {x, y, 150, 150},
        {x, y, 140, 170},
        {x, y, 200, 200},
        {x, y, 150, 180},
        {x, y, 120, 150},
        {x, y, 70, 220}
    };

    SDL_Surface *drevSurface = IMG_Load(fileNames[i]);
    SDL_Texture *drev = SDL_CreateTextureFromSurface(globalRenderer, drevSurface);
    SDL_Rect StaroDst = sizes[i];

    SDL_FreeSurface(drevSurface);
    SDL_RenderCopy(globalRenderer, drev, NULL, &StaroDst);
    SDL_DestroyTexture(drev);
}

