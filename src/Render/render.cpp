#include "render.hpp"
#include <vector>
#include <iterator>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <fstream>


void Render(std::vector<Baraba>&vectBar,Player &player,std::vector<Staroselci>&vectStaro,std::vector<Ogenj> &vectOg,int st_Ognjev,std::vector<Drevo> & vectDrev,int st_levla) { //* je funkcija, ki izpiše vse like
    Back back;
    std::ifstream datai ("replay.bin",std::ios::binary | std::ios::in | std::ios::app);
    if(!datai.is_open()){
        std::cout<<"Napaka z player.bin pri izpisu"<<std::endl;
    } 
    if(st_levla<4){ 
        back.Render();
        for (int i=0;i<vectDrev.size();i++){
            vectDrev[i].Render(i);
        }
        for(std::vector<Baraba>::iterator it=vectBar.begin();it!=vectBar.end();it++){// izriše vsak element vektorja
            it->Render(); //* tuki pa polega tega, da izriše vsak posamezen element, ga tudi pomakne bližje playerju
        }
        
        for(int i=0;i<st_Ognjev;i++){ //izriše ognje (vsakič bo enega več, saj želimo, da s časom narašča število ognjev )
            vectOg[i].Render(); 
        }
        for(std::vector<Staroselci>::iterator it=vectStaro.begin();it!=vectStaro.end();it++){// izriše vsak element vektorja
            it->Render(); //* tuki pa polega tega, da izriše vsak posamezen element, ga tudi pomakne bližje playerju
        }
        player.Render();
        SDL_Delay(125);
    } else {
        while(datai.read((char*)&player,sizeof(player))){
            back.Render();
            player.Render();
            SDL_Delay(125);
        }
        std::ofstream datao ("replay.bin",std::ios::binary | std::ios::out | std::ios::trunc);  //* odpiranje ofstreama, ker z trunc (truncate) zastavico izbrišemo vsebino replay.bin po izpisu
        datao.close();
    }
    datai.close();
}

