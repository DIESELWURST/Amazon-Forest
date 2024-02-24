#include "render.hpp"
#include "mobs.hpp"
#include <vector>
#include <iterator>
 std::vector<Baraba>vectBar(5);
 Player player;
void Render() { //* je funkcija, ki izpiše vse like
    Back back;
    back.Render();
    for(std::vector<Baraba>::iterator it=vectBar.begin();it!=vectBar.end();it++){
        it->Render();
    }
    player.Render();

}
