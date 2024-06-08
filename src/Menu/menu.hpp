#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL_image.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "player.hpp"

class Menu {
private:
    int heightMod,widthMod;
public:
    void init(SDL_Renderer * renderer,SDL_Window * window,int & SCREEN_HEIGHT,int & SCREEN_WIDTH,int & st_levla, Player & player);
    int vrniHeightMod() const {return heightMod;}
    int vrniWidthMod() const {return widthMod;}
     
};

#endif // MENU_HPP
