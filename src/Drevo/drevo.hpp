#ifndef DREVO_HPP
#define DREVO_HPP

#include "mobs.hpp"
#include <vector>

class Drevo : public Mobs {
public:
    bool je_posekan;
    void Render(int i);
    void fillDrev(std::vector<Drevo>& vectDrev);
};

#endif // DREVO_HPP
