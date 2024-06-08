#ifndef UPDATE_HPP
#define UPDATE_HPP

#include <vector>
#include "baraba.hpp"
#include "player.hpp"
#include "staroselci.hpp"
#include "drevo.hpp"
#include "ogenj.hpp"
#include <SDL2/SDL.h>

void Update_Mobs(std::vector<Baraba>& vectBar, Player& player, std::vector<Staroselci>& vectStaro, std::vector<Ogenj>& vectOg, std::vector<Drevo>& vectDrev, int st_levla,Uint32 Cas_o,int SCREEN_HEIGHT,int SCREEN_WIDTH);

#endif // UPDATE_HPP
