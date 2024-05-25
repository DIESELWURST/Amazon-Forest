#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "mobs.hpp"

class Player: public Mobs {
public:
    Player(); //* metoda za risanje  
    void Render();
    void Update ();
    bool Borders(int minX, int maxX, int minY, int maxY)  ; //* metoda za omejevanje premikov (const je tm samo, da povem da ne bomo spremenil vrednosti ničesar)
};

#endif // PLAYER_HPP
