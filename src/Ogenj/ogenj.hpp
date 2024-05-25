#ifndef OGENJ_HPP
#define OGENJ_HPP

#include "mobs.hpp"
#include "player.hpp"
#include <vector>

class Ogenj : public Mobs {
public:
    void Render();
    void Update(std::vector<Ogenj>& vectOg, Player& player, int st_ognja, int st_levla);
    void fillOgenj(std::vector<Ogenj>& vectOg);
    bool Borders(int minX, int maxX, int minY, int maxY);
};

#endif // OGENJ_HPP
