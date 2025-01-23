#include "Game.hpp"
#include <SDL.h>
#include <SDL_render.h>

#include "Util/Logger.hpp"


Game::Game() {
    isRunning = false;
    window = nullptr;
    renderer = nullptr;
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

void Game::update() {

}

void Game::startLoop() {
    while (isRunning) {
        handleEvents();
        update();
        render();
    }
    clean();
}

void Game::render() {

    SDL_RenderClear(renderer);
    // Add stuff to render here
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    Logger::log("Game cleaned");
}