#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "mobs.hpp"
#include <SDL2/SDL_image.h>
class Player: public Mobs {
private:
    char ime[75];
    int tocke;
    bool Prekoracen_cas;
public:
    Player(); //* metoda za risanje  
    void Render(SDL_Renderer* renderer);
    void Update (int SCREEN_HEIGHT,int SCREEN_WIDTH,Uint32 Cas_o,int st_levla);
    bool Borders(int minX, int maxX, int minY, int maxY)  ; //* metoda za omejevanje premikov (const je tm samo, da povem da ne bomo spremenil vrednosti ničesar)
    int getTocke()  { return tocke; }
    bool jePrekoraceno()  { return Prekoracen_cas;}
    const char * getIme() const { return ime;}
    void setIme (const char * Newname);
    void addTocke (int addedPoints);
};

#endif // PLAYER_HPP
