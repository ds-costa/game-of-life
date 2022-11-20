#include "src/Game.hpp"

int main() {
    Game game(1280, 720, "Conway's Game of Life");
    game.Run();
    return 0;
}