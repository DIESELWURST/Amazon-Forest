#include "update.hpp"
#include <iostream>
#include <fstream>
#include <vector>
//* funkicja, ki posodobila pozicije likov
void Update (std::vector<Baraba> & vectBar,Player & player,std::vector<Staroselci> &vectStaro,std::vector <Ogenj> & vectOg,std::vector<Drevo> & vectDrev,int st_levla){
    std::ofstream datao ("replay.bin",std::ios::binary | std::ios::out | std::ios::app);
    player.Update();
    datao.write((char *)&player,sizeof(player));
    for(int i=0;i<vectOg.size();i++){ 
        vectOg[i].Update(vectOg,player,i,st_levla);
       
    }
    for(int i=0;i<vectStaro.size();i++){
        vectStaro[i].Update(vectBar,vectOg,player,vectStaro,i);
    }
    for(int i=0;i<vectBar.size();i++){ 
        vectBar[i].Update(vectBar,player,vectDrev,i);
    }
    datao.close();
} 



   