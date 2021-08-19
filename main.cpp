#include "src/Game.hpp"

int main() {
    Game game(800, 600, "Conway's Game of Life");
    game.Run();
    return 0;
}