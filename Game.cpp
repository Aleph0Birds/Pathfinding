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
}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    isRunning = false;
    if (!SDL_Init(SDL_INIT_EVERYTHING)) // Success is 0
        Logger::log("Successfully initialize SDL");
    else return Logger::log("Failed to initialize SDL");


    window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
    if (window) Logger::log("Successfully create window");
    else return Logger::log("Failed to create window");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer) Logger::log("Successfully create renderer");
    else return Logger::log("Failed to create renderer");
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
    const static SDL_Rect rect = {0, 0, 0, 0};
    SDL_FillRect(nullptr, &rect, 0);
    SDL_RenderFillRect(renderer, &rect);

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

void Game::setDeltaTime(uint32_t deltaTimeMs) {
    this->deltaTimeMs = deltaTimeMs;
}