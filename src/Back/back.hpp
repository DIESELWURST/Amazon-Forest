#ifndef BACK_HPP
#define BACK_HPP
#include <SDL2/SDL_image.h>
class  Back {
public:
    void Render(SDL_Renderer * renderer,int SCREEN_HEIGHT,int SCREEN_WIDTH);
    void Start (SDL_Renderer * renderer,SDL_Window *window ,int SCREEN_HEIGHT,int SCREEN_WIDTH);
};

#endif // BACK_HPP
