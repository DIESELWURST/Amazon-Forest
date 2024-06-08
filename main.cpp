// main.cpp
#include "game.hpp"

int main(int argc, char** argv) {
    Game game;
    if (game.Init()) {
        game.Run();
    }
    return 0;
}
