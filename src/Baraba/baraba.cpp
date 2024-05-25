#include "baraba.hpp"
#include <cmath>
#include <time.h>
#include <SDL2/SDL_image.h>

extern SDL_Renderer *globalRenderer; //* globalna spremenljivka za renderer
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

void Baraba:: fillBaraba(std::vector<Baraba>&vectBar){
    srand(time(NULL));
    for(std::vector<Baraba>::iterator it=vectBar.begin();it!=vectBar.end();it++){ //s to zanko napolnimo vektor z objekti Baraba
        int spawnQuotient= rand()%100;//* je spremenljivka s katero določimo, pri kateri luknji bo spawn objekta
        if(spawnQuotient<50){ //*če bo manjše od 50 se bo objekt (Baraba) spawnal na levi luknji
            it->x=100;
            it->y=200;
            it-> radius=60;
        }else { //* če bo >=50 bo imel spawn na desni luknji
            it->x=1200;
            it->y=150;
            radius=60;
        }
    }
}


bool Baraba:: Borders (int minX, int maxX, int minY, int maxY)  {
    return Mobs::Borders (minX,maxX,minY,maxY);
 }

void Baraba:: Update (std::vector<Baraba>&vectBar,Player &player,std::vector<Drevo> &vectDrev,int count) {
    int min_x=0; //* s tem gledamo ali je barabi bližji player ali katerkoli drevo
    int min_y=0;
    int movementSpeed=25;
     //s tem pogledamo če  je Player v radiju 
    int player_dist=std::sqrt(std::pow(player.getX() - x, 2) + std::pow(player.getY() - y, 2));//* gledamo če je player v radiju z uporabe formule za razdaljo med 2 točkama (d= sqrt( (x2-x1)^2 + (y2-y1)^2 ))
    if(player_dist<radius){ 
        min_y=player.getY();
        min_x=player.getX();
    }
        
    int drev_dist=0;
        for(int i=0;i<vectDrev.size();i++){ //s tem pogledamo katero drevo je najbližje
            drev_dist=std::sqrt(pow((vectDrev[i].getX()-x),2) + pow((vectDrev[i].getY()-y),2));
            if(drev_dist<radius && drev_dist<player_dist){ // gledamo če je razdalja med drevesom in barabo manjša od radija
                min_x=vectDrev[i].getX();
                min_y=vectDrev[i].getY();
            } else { //* s tem se bo Baraba naključno premaknila nekam, če ničesar ni v njenem view-u
                x+=(rand()%3-1)*movementSpeed;
                y+=(rand()%3-1)*movementSpeed;    
            }
        }
    if (x < min_x) { //* pomikamo se proti namanjši vrednosti
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

       for(int i=0;i<vectDrev.size();i++){ // s tem gledamo, če je radiju kakšno drevo
            if (std::sqrt(pow((vectDrev[i].getX()-x),2) + pow((vectDrev[i].getY()-y),2))< radius) { //* isto kot zgornja koda, ampak samo preverjamo za Staroselce
                 vectDrev[i].je_posekan= true;
            }
       }
       for(int i=0;i<vectBar.size();i++){
            if ((abs(vectBar[i].x-player.getX())< player.getRadius() && abs(vectBar[i].y-player.getY())< player.getRadius())){
                    vectBar.erase(vectBar.begin()+i); //* če sta player in 1 baraba sama izbiršemo barabo
            }
       }
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
    SDL_FreeSurface(barSurface);
    SDL_RenderCopy(globalRenderer, bar, NULL, &barDst);
    SDL_DestroyTexture(bar);
}