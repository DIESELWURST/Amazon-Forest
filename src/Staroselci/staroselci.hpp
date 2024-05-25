#ifndef STAROSELACI_HPP
#define STAROSELACI_HPP

#include "mobs.hpp"
#include "baraba.hpp"
#include "player.hpp"
#include "ogenj.hpp"

class Staroselci : public Mobs {
public:
    void Render();
    void Update(std::vector<Baraba>& vectBar, std::vector<Ogenj>& vectOg, Player& player, std::vector<Staroselci>& vectStaro, int st_staroselca);
    void fillStaro(std::vector<Staroselci>& vectStaro);
    bool Borders(int minX, int maxX, int minY, int maxY);
};

#endif // STAROSELACI_HPP
