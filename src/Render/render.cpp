#include "render.hpp"
#include <vector>
#include <iterator>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <fstream>


void Render_Mobs(std::vector<Baraba>&vectBar,Player &player,std::vector<Staroselci>&vectStaro,std::vector<Ogenj> &vectOg,int st_Ognjev,std::vector<Drevo> & vectDrev,int st_levla,SDL_Renderer *renderer,int SCREEN_HEIGHT,int SCREEN_WIDTH) { //* je funkcija, ki izpiše vse like
    Back back;
        back.Render(renderer,SCREEN_HEIGHT,SCREEN_WIDTH);
        for (int i=0;i<vectDrev.size();i++){
            vectDrev[i].Render(i,renderer);
        }
        for(std::vector<Baraba>::iterator it=vectBar.begin();it!=vectBar.end();it++){// izriše vsak element vektorja
            it->Render(renderer); //* tuki pa polega tega, da izriše vsak posamezen element, ga tudi pomakne bližje playerju
        }
        
        for(int i=0;i<st_Ognjev;i++){ //izriše ognje (vsakič bo enega več, saj želimo, da s časom narašča število ognjev )
            vectOg[i].Render(renderer); 
        }
        for(std::vector<Staroselci>::iterator it=vectStaro.begin();it!=vectStaro.end();it++){// izriše vsak element vektorja
            it->Render(renderer); //* tuki pa polega tega, da izriše vsak posamezen element, ga tudi pomakne bližje playerju
        }
        player.Render(renderer);
        SDL_Delay(125);
}

