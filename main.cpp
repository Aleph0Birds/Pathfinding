#include "Game.hpp"
#include "Util/Logger.hpp"

int main() {
    Game game{};
    game.init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, false);
    game.setGrid(50, 50);
    game.setDeltaTime(8); // >~60fps
    game.startLoop();

    Logger::log("Game closed");
    return 0;
}
