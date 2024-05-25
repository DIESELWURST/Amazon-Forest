#ifndef LEVEL_HPP
#define LEVEL_HPP

class Level {
public:
    int st_Bar,st_Og,st_Staro;
    int getBar() const { return st_Bar;}
    int getOg() const { return st_Og;}
    int getStaro() const { return st_Staro;}
    void fillLevel( int st_levla);
};

#endif // LEVEL_HPP
