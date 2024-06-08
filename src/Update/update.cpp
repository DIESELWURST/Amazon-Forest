#include "update.hpp"
#include <iostream>
#include <fstream>
#include <vector>
//* funkicja, ki posodobila pozicije likov
void Update_Mobs (std::vector<Baraba> & vectBar,Player & player,std::vector<Staroselci> &vectStaro,std::vector <Ogenj> & vectOg,std::vector<Drevo> & vectDrev,int st_levla, Uint32 Cas_o,int SCREEN_HEIGHT,int SCREEN_WIDTH){
    std::ofstream datao ("replay.bin",std::ios::binary | std::ios::out | std::ios::app);//* zapisujemo pozicijo player-ja v player.bin
    player.Update(SCREEN_HEIGHT,SCREEN_WIDTH,Cas_o,st_levla);
    datao.write((char *)&player,sizeof(player));
    for(int i=0;i<vectOg.size();i++){ 
        vectOg[i].Update(vectOg,player,i,st_levla,SCREEN_HEIGHT, SCREEN_WIDTH);
       
    }
    for(int i=0;i<vectStaro.size();i++){
        vectStaro[i].Update(vectBar,vectOg,player,vectStaro,i,SCREEN_HEIGHT,SCREEN_WIDTH);
    }
    for(int i=0;i<vectBar.size();i++){ 
        vectBar[i].Update(vectBar,player,vectDrev,i,SCREEN_HEIGHT,SCREEN_WIDTH);
    }
    datao.close();
} 



   