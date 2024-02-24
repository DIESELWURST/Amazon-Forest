#pragma once
#include <vector>
class Mobs { // abstraktni razred iz katerega bomo izpeljevali druge entity-e
protected:
    int x,y;// kje se nahaja središčnica kroga
    int radius;
public:  
    virtual void Render()=0; //* metoda za risanje  
};

class Player: public Mobs {
public:
    Player();
    void Render();
    bool Borders(int minX, int maxX, int minY, int maxY)  ; //* metoda za omejevanje premikov (const je tm samo, da povem da ne bomo spremenil vrednosti ničesar)
};

class Baraba : public Mobs {
public:
    std::vector<Baraba> vectBar;
    Baraba();
    void Render();
    void Borders(int minX, int maxX, int minY, int maxY);//* metoda za omejevanje premikov (const je tm samo, da povem da ne bomo spremenil vrednosti ničesar)
};

class  Back: public Mobs {
public:
    void Render();
    void Start();
};



