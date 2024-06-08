#include "render.hpp"
#include "menu.hpp"
#include "level.hpp"
#include "back.hpp"
#include "update.hpp"
#include "player.hpp"
#include "baraba.hpp"
#include "drevo.hpp"
#include "staroselci.hpp"
#include "mobs.hpp"
#include "ogenj.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
//#include <SDL2/SDL_ttf.h>

//* - Razlaga ukazov,funkcij,spremenljivk,pogojev
//  - Razlaga zank,struktur,objektov 
//? -


int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //* s tem poveš compilerju, da boš začel delat z SDL
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        printf("VSE je fuč");
        return 1;
    }
    
    Back inititalise;// Razred Back je tu deklariran, saj bo prvi objekt v levlu , ki bo izpisan in ga potrebujemo za klic funkcije start
    inititalise.Start();// funkcija start bo deklarirala renderer in odprla okno
    Menu meni;
    int st_levla = meni.init(); //* stevilka  s katero določamo kateri lvl bo igran
    Level Lvl;
    Lvl.fillLevel(st_levla);
    std::vector<Baraba> vectBar(Lvl.st_Bar);
    Baraba Bar;
    Bar.fillBaraba(vectBar);
    Player player;
    std::vector<Ogenj> vectOg(Lvl.st_Og);
    Ogenj Og;
    Og.fillOgenj(vectOg);
    float st_Ognjev = 1; //* stevilo s katerim omejujemo stevilo ognjev na zaslonu (da se konstantno regenerirajo)
    Staroselci Staro;
    std::vector<Staroselci> vectStaro(Lvl.st_Staro);
    Staro.fillStaro(vectStaro);
    Drevo Drev;
    std::vector<Drevo> vectDrev(9);
    Drev.fillDrev(vectDrev);
    bool running = true;
    bool replay=false;
    if (st_levla<4){ //* če ni replay na začetku izvajanja odpremo datoteko, da bo lahko izrisali samo premike iz nazadnje igre
        std::ofstream datao ("replay.bin",std::ios::binary);//*s tem ko beremo datoteko se izbriše vsebina datoteke
    }
    while (running) { // while loop, ki samo preverja, če se je kej zgodil ( tuki posebi gleda če smo zaprl program)
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }
        
        if (st_levla<4) { //* če ne izberemo replay moda
            Update(vectBar, player, vectStaro, vectOg, vectDrev, st_levla);
            Render(vectBar, player, vectStaro, vectOg, st_Ognjev, vectDrev, st_levla);
        } else { //* če se bo izvajal replay mode
            Render(vectBar, player, vectStaro, vectOg, st_Ognjev, vectDrev, st_levla);
            break;
        }

        if (st_Ognjev * 80 * 100 > 1280 * 720 * 0.7) { //* če ognji zakrivajo 70% okna se bo level zaključil (80*100 -ploščina slike ognja in 1280*720- ploščina okna w*h)
           std::cout << "Skoraj! Zgleda kot da ti primanjkuje borbenega duha.";
            break;
        }
        st_Ognjev >= vectOg.size() ? st_Ognjev = vectOg.size() : st_Ognjev++; //* ta pogoj je samo zgornja meja ognjov,ki jih bomo renderal (če je true se poveča za 1, če je false samo na maks postavljamo st)
     }
    IMG_Quit();
    return 0;
}
