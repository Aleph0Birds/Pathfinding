#include <ctime>
#include <iostream>
#include <ostream>
#include <SDL_log.h>
#include <bits/locale_classes.h>

#include "Game.hpp"
#include "Util/Logger.hpp"

int main() {
    Game game{};
    fflush(stdout);
    game.init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, false);
    game.setGrid(50, 50);
    game.setDeltaTime(10); // >~30ups
    game.setTargetFps(60);
    game.startLoop();

    Logger::log("Game closed");
    return 0;
}
