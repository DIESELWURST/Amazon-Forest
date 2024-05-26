#include "staroselci.hpp"
#include <time.h>
#include <SDL2/SDL_image.h>
extern SDL_Renderer *globalRenderer; //* globalna spremenljivka za renderer
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
void Staroselci :: fillStaro (std::vector<Staroselci>&vectStaro) {
    int spawnQuotient;//* s tem določemo na kateremu izmed 4 možnih spwanov se bo pojavil 1 staroselec
    for(std::vector<Staroselci>:: iterator it=vectStaro.begin();it!=vectStaro.end();it++){
        spawnQuotient=rand()%100;
        if(spawnQuotient>=0 && spawnQuotient<25){
            it->x=100;
            it->y=100;
            it->radius=60;
        } else if (spawnQuotient>=25 && spawnQuotient<49){
            it->x=100;
            it->y=600;
            it->radius=60;
        }else if (spawnQuotient>=50 && spawnQuotient<75){
            it->x=1200;
            it->y=50;
            it->radius=60;
        }else if (spawnQuotient>=75 && spawnQuotient<99){
            it->x=1125;
            it->y=575;
            it->radius=60;
        }
    }
}
bool Staroselci:: Borders (int minX, int maxX, int minY, int maxY)  {
    return Mobs::Borders (minX,maxX,minY,maxY);
 }

void Staroselci:: Render(){
    SDL_Surface *staroSurface=IMG_Load("assets/goodie.png");
    if(!staroSurface){
         printf("Error: Failed to load player image\nSDL_Image Error: '%s'\n", IMG_GetError());        
    } 
    
    SDL_Texture *staro = SDL_CreateTextureFromSurface(globalRenderer , staroSurface);
    if(!staro){
        printf("Error: Failed to create texture\n");     
    }

    SDL_Rect StaroDst = {
        .x = x, //* na katerem x-u bos postavu sliko
        .y = y, //* na keretem y-u bos postavu sliko
        .w = 50, //* širina slike, ki jo bomo dodali                      
        .h = 50,                      
    };
    SDL_FreeSurface(staroSurface);
    SDL_RenderCopy(globalRenderer, staro, NULL, &StaroDst);
    SDL_DestroyTexture(staro);
}
 void Staroselci:: Update (std::vector<Baraba>& vectBar, std::vector<Ogenj>& vectOg, Player & player, std::vector<Staroselci>& vectStaro,int  st_staroselca){
    int min_x=vectBar[0].getX(); 
    int min_y=vectBar[0].getY();
    int movementSpeed=25;
    int barabeCount=0;
    for(int i=0;i<vectBar.size();i++){ //s tem pogledamo katera baraba je najbližja
            if (abs(x-vectBar[i].getX())<min_x && abs(y-vectBar[i].getY())<min_y){ //* gledamo, če je razdalja do barabe manjša od radija Staroselcev
                min_x=vectBar[i].getX();
                min_y=vectBar[i].getY();
                barabeCount++; //* tuki še hkrati gledamo. če je v radiju Staroselca več kot ena baraba
            }
        
    }
    for(int i=0;i<vectOg.size();i++){ //s tem pogledamo kateri ogenj je najbližji (ognji so bolj pomembni, zato se bodo prvo napotili k njim)
            if (abs(x-vectOg[i].getX())<min_x && abs(y-vectOg[i].getY())<min_y){
                min_x=vectOg[i].getX();
                min_y=vectOg[i].getY();
            
        } else { //* s tem se bo Staroselec naključno premaknil nekam, če ničesar ni v njegovem view-u
            x+=(rand()%3-1)*movementSpeed;
            y+=(rand()%3-1)*movementSpeed;    
        }
    }

    if (x < min_x) { //* s tem se bližajo Staroselci po y-osi
        x += movementSpeed;
    } else if (x > min_x) {
        x -= movementSpeed;
    } 

    if (y < min_y) { 
        y += movementSpeed;
    } else if (y > min_y) {
        y -= movementSpeed;
    }
    Borders(0, SCREEN_WIDTH - 50, 0, SCREEN_HEIGHT - 50);

       for(int i=0;i<vectOg.size();i++){ // s tem staroselci pogasijo ogenj
            if (abs(vectOg[i].getX()-x)< radius && abs(vectOg[i].getY()-y)< radius) { //* isto kot zgornja koda, ampak samo preverjamo za Staroselce
                 vectOg.erase(vectOg.begin()+i);//* če je izbrišemo ogenj ven iz vectOg
            }
        }

        for(int i=0;i<vectBar.size();i++){ // s tem staroselci eliminirajo barabe
            if (abs(vectBar[i].getX()-x)< radius && abs(vectBar[i].getY()-y)< radius) { //* isto kot zgornja koda, ampak samo preverjamo za Staroselce
                 if(barabeCount>=2 && (abs(player.getX()-x)< radius && abs(player.getY()-y)< radius)) { //* preverjamo, če je 2+ barab v radiju in če je player
                    vectBar.erase(vectBar.begin()+i);//* če je izbrišemo eno barabo iz vectBar
                 } else if (barabeCount>=2 && !(abs(player.getX()-x)< radius && abs(player.getY()-y)< radius)){//* preverjamo, če 2+ barab in ni playerja
                        vectStaro.erase(vectStaro.begin()+i); //* če sta izbrišemo enega staroselca iz vectStaro
                 } else  {
                    vectBar.erase(vectBar.begin()+i); //* če je samo 1 barabo jo lahko izbriše 1 staroselec
                 }
            } 
             
        }
    
 }