#ifndef DREVO_HPP
#define DREVO_HPP

#include "mobs.hpp"
#include "player.hpp"
#include <vector>
#include <SDL2/SDL_image.h>
class Drevo : public Mobs {
public:
    bool je_posekan;
    void Render(int i,SDL_Renderer * renderer);
    void fillDrev(std::vector<Drevo>& vectDrev);
};

#endif // DREVO_HPP
