#ifndef OGENJ_HPP
#define OGENJ_HPP

#include "mobs.hpp"
#include "player.hpp"
#include <vector>

class Ogenj : public Mobs {
public:
    void Render(SDL_Renderer * renderer);
    void Update(std::vector<Ogenj>& vectOg, Player& player, int st_ognja, int st_levla,int SCREEN_HEIGHT,int SCREEN_WIDTH);
    void fillOgenj(std::vector<Ogenj>& vectOg,int SCREEN_HEIGHT,int SCREEN_WIDTH);
    bool Borders(int minX, int maxX, int minY, int maxY);
};

#endif // OGENJ_HPP
