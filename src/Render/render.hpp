#ifndef RENDER_HPP
#define RENDER_HPP

#include "back.hpp"
#include "player.hpp"
#include "baraba.hpp"
#include "staroselci.hpp"
#include "drevo.hpp"
#include "ogenj.hpp"

void Render(std::vector<Baraba>& vectBar, Player& player, std::vector<Staroselci>& vectStaro, std::vector<Ogenj>& vectOg, int st_Ognjev, std::vector<Drevo>& vectDrev, int st_levla);

#endif // RENDER_HPP
