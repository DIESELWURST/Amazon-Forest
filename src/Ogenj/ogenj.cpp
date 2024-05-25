#include "ogenj.hpp"
#include <SDL2/SDL_image.h>


extern SDL_Renderer *globalRenderer; //* globalna spremenljivka za renderer
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
void Ogenj:: Render(){
   
   
     SDL_Surface *ogSurface=IMG_Load("assets/ogenj.png");
    if(!ogSurface){
         printf("Error: Failed to load player image\nSDL_Image Error: '%s'\n", IMG_GetError());        
    } 
    
    SDL_Texture *og = SDL_CreateTextureFromSurface(globalRenderer , ogSurface);
    if(!og){
        printf("Error: Failed to create texture\n");     
    }

    SDL_Rect ogDst = {
        .x = x, //* na katerem x-u bos postavu sliko
        .y = y, //* na keretem y-u bos postavu sliko
        .w = 80, //* širina slike, ki jo bomo dodali                      
        .h = 100,                      
    };

    SDL_FreeSurface(ogSurface);
    SDL_RenderCopy(globalRenderer, og, NULL, &ogDst);
    SDL_DestroyTexture(og);


}

void Ogenj:: fillOgenj(std::vector<Ogenj>&vectOg){
        for(int i=0;i<vectOg.size();i++){
                vectOg[i].y=rand()%600; //* 600 in 1200 , ker tako zgleda boljše
                vectOg[i].x=rand()%1210;
            Borders(0, SCREEN_WIDTH - 50, 0, SCREEN_HEIGHT - 50);
    }
}
 bool Ogenj:: Borders (int minX, int maxX, int minY, int maxY)  {
    return Mobs::Borders (minX,maxX,minY,maxY);
 }
void Ogenj:: Update (std::vector<Ogenj>&vectOg,Player &player,int count,int st_levla) { 
       if (abs(x-player.getX())<player.getRadius() && abs(y-player.getY())<player.getRadius() ) { //* samo pogledamo če je razdalja med playerjem in ognjem manjša od radija playerja
                vectOg.erase(vectOg.begin()+count);//* če je izbrišemo ogenj ven iz vectOg
            }
            Borders(0, SCREEN_WIDTH - 50, 0, SCREEN_HEIGHT - 50);
            if(vectOg.size() <=5){ //* s tem povzročimo, da se ognji refillajo, ko jih ostane 5
            vectOg.resize(50*st_levla);
            fillOgenj(vectOg);
        }

}
