#ifndef STAROSELACI_HPP
#define STAROSELACI_HPP

#include "mobs.hpp"
#include "baraba.hpp"
#include "player.hpp"
#include "ogenj.hpp"
#include <SDL2/SDL_image.h>
class Staroselci : public Mobs {
public:
    void Render(SDL_Renderer * renderer);
    void Update(std::vector<Baraba>& vectBar, std::vector<Ogenj>& vectOg, Player& player, std::vector<Staroselci>& vectStaro, int st_staroselca,int SCREEN_HEIGHT,int SCREEN_WIDTH);
    void fillStaro(std::vector<Staroselci>& vectStaro);
    bool Borders(int minX, int maxX, int minY, int maxY);
};

#endif // STAROSELACI_HPP
