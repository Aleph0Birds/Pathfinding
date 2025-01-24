#include "Game.hpp"

#include <chrono>
#include <SDL.h>
#include <SDL_render.h>

#include "Util/Logger.hpp"


Game::Game() {
    isRunning = false;
    window = nullptr;
    renderer = nullptr;
    deltaTimeMs = 16;
    grid = nullptr;
    lastUpdateTick = SDL_GetTicks();
    windowDimensions = {0, 0};
}

Game::~Game() {

}

void Game::init(
        const char* title,
        const int xpos,
        const int ypos,
        const int width,
        const int height,
        const bool fullscreen
    ) {
    isRunning = false;
    if (!SDL_Init(SDL_INIT_EVERYTHING)) // Success is 0
        Logger::log("Successfully initialize SDL");
    else return Logger::err("Failed to initialize SDL");

    window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
    if (window) Logger::log("Successfully create window");
    else return Logger::err("Failed to create window");

    windowDimensions = {width, height};

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer) Logger::log("Successfully create renderer");
    else return Logger::err("Failed to create renderer");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    isRunning = true;
    lastUpdateTick = SDL_GetTicks();
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update(uint32_t deltaTimeMs) {

}

void Game::render() {
    SDL_RenderClear(renderer);
    // Add stuff to render here
    SDL_SetRenderDrawColor(renderer, 0, 60, 100, 255);

    if (grid) grid->draw();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
}

void Game::startLoop() {
    while (isRunning) {
        handleEvents();
        checkUpdate();
        render();
    }
    clean();
}

void Game::checkUpdate() {
    if (!isRunning) return;
    const uint32_t curTick = SDL_GetTicks();
    const uint32_t deltaTick = curTick - lastUpdateTick;

    if (deltaTick >= deltaTimeMs) {
        update(deltaTick);
        lastUpdateTick = curTick;
    };
}

void Game::clean() const {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    Logger::log("Game cleaned");
}

void Game::setDeltaTime(const uint32_t deltaTimeMs) {
    this->deltaTimeMs = deltaTimeMs;
}

void Game::setGrid(const uint8_t width, const uint8_t height) {
    grid = new Grid(this, width, height);
}

SDL_Renderer* Game::getRenderer() const {
    return renderer;
}

std::pair<int, int> Game::getDimensions() const {
    return windowDimensions;
}
