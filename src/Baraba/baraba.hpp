#ifndef BARABA_HPP
#define BARABA_HPP

#include "mobs.hpp"
#include "player.hpp"
#include "drevo.hpp"
#include <vector>

class Baraba : public Mobs {
public:
    std::vector<Baraba> vectBar;
    void fillBaraba(std::vector<Baraba>& vectBar);
    void Render();
    void Update(std::vector<Baraba>& vectBar, Player& player, std::vector<Drevo>& vectDrev, int st_barabe);
    bool Borders(int minX, int maxX, int minY, int maxY);
};

#endif // BARABA_HPP
