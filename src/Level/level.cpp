#include "level.hpp"
#include <iostream>
void Level:: fillLevel (int st_levla) {
        Cas_o=10000/st_levla; //* časovna omjeitev za levle (če jo player prekorači se se mu bo odštelo nekaj točk)
        st_Bar=5*st_levla;//*15*(i+1);
        st_Staro=10/st_levla;//*15/(i+1);
        st_Og=50*(st_levla);
}