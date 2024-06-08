#ifndef GAME_HPP
#define GAME_HPP

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
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    int st_levla;
    float st_Ognjev;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

    Level lvl;
    Menu menu;
    Player player;
    std::vector<Baraba> vectBar;
    std::vector<Staroselci> vectStaro;
    std::vector<Ogenj> vectOg;
    std::vector<Drevo> vectDrev;
    
public:
    Game();
    ~Game();
    
    bool Init();
    void Run();
    void SaveGame();
    bool LoadGame();
    void HandleEvents();
    void Update();
    void Render();
    void ReplayGame();
    void updateLeaderboard();
    void displayLeaderboard();

};

#endif