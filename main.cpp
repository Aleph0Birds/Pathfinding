#include "Game.hpp"
#include "Util/Logger.hpp"

int main() {
    Game game{};
    game.init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    game.setGrid(20, 20);
    game.setDeltaTime(8); // >~60fps
    game.startLoop();

    Logger::log("Game closed");
    return 0;
}
