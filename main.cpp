#include "Game.hpp"
#include "Util/Logger.hpp"

int main() {
    Game game{};
    game.init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, false);
    game.setGrid(30, 30);
    game.setDeltaTime(16); // >~60fps
    game.startLoop();

    Logger::log("Game closed");
    return 0;
}
