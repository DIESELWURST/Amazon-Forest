#ifndef LEVEL_HPP
#define LEVEL_HPP
#include <SDL2/SDL.h>
class Level {
private:
    int st_Bar,st_Og,st_Staro;
    Uint32 Cas_o;
public:
    int getBar() const { return st_Bar;}
    int getOg() const { return st_Og;}
    int getStaro() const { return st_Staro;}
    void setCas(Uint32 cas) { Cas_o = cas; }
    Uint32 getCas() { return Cas_o;}
    void fillLevel( int st_levla);
};

#endif // LEVEL_HPP
