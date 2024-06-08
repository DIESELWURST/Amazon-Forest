#ifndef BARABA_HPP
#define BARABA_HPP

#include "mobs.hpp"
#include "player.hpp"
#include "drevo.hpp"
#include <vector>
#include <SDL2/SDL_image.h>
class Baraba : public Mobs {
public:
    std::vector<Baraba> vectBar;
    void fillBaraba(std::vector<Baraba>& vectBar);
    void Render(SDL_Renderer * renderer);
    void Update(std::vector<Baraba>& vectBar, Player& player, std::vector<Drevo>& vectDrev, int st_barabe,int SCREEN_HEIGHT,int SCREEN_WIDTH);
    bool Borders(int minX, int maxX, int minY, int maxY);
};

#endif // BARABA_HPP
