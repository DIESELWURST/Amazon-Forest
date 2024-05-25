#include "mobs.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

    
extern SDL_Window *globalWindow; //* globalna spremenljivka za window + vse extern spremenljivke so v datoteki globals
extern SDL_Renderer *globalRenderer; //* globalna spremenljivka za renderer
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;



bool Mobs:: Borders(int minX, int maxX, int minY, int maxY)  { //* metoda za omejevanje premikov
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
    