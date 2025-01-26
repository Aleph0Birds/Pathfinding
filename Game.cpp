#include "Game.hpp"

#include <chrono>
#include <SDL.h>
#include <SDL_render.h>

#include "Util/Logger.hpp"


Game::Game() {
    isRunning = false;
    window = nullptr;
    renderer = nullptr;
    renderTarget = nullptr;
    deltaTimeMs = 16;
    grid = nullptr;
    lastUpdateTick = SDL_GetTicks();
    windowDimensions = {0, 0};
    scale = 1;
    worldRectCentered = {};
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
    if (!SDL_Init(SDL_INIT_EVERYTHING)) // Success is 0
        Logger::log("Successfully initialize SDL");
    else return Logger::err("Failed to initialize SDL");

    uint32_t flags = (fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN)
        | SDL_WINDOW_RESIZABLE;

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window) Logger::log("Successfully create window");
    else return Logger::err("Failed to create window");

    windowDimensions = {width, height};

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer) Logger::log("Successfully create renderer");
    else return Logger::err("Failed to create renderer");

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    renderTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, worldSizeX, worldSizeX);
    worldRectCentered = {0, 0, worldSizeX, worldSizeY};
    handleResize(width, height);

    isRunning = true;
    lastUpdateTick = SDL_GetTicks();
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_WINDOWEVENT:
                handleWindowEvents(&event);
                break;
            default:
                break;
        }
    }
}

void Game::update(uint32_t deltaTimeMs) {

}

void Game::render() const {
    if (!isRunning) return;
    SDL_RenderClear(renderer);
    // Add stuff to render here
    SDL_SetRenderTarget(renderer, renderTarget);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &worldRect);
    if (grid) grid->draw();

    SDL_SetRenderTarget(renderer, nullptr);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderCopy(renderer, renderTarget, nullptr, &worldRectCentered);
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

void Game::handleWindowEvents(const SDL_Event* event) {
    switch (event->window.event) {
        case SDL_WINDOWEVENT_RESIZED:
            handleResize(event->window.data1, event->window.data2);
            break;
        default: break;
    }
}

void Game::handleResize(int width, int height) {
    windowDimensions = {width, height};
    scale = std::min(static_cast<float>(width) / worldSizeX, static_cast<float>(height) / worldSizeY);
    SDL_RenderSetScale(renderer, scale, scale);
    if (width > height) {
        worldRectCentered.x = (width - height) / 2 / scale ;
        worldRectCentered.y = 0;
        //worldRectCentered = {0, (height - width) / 2, width, width};
    } else {
        worldRectCentered.y = (height - width) / 2 / scale;
        worldRectCentered.x = 0;
        //worldRectCentered = {(width - height) / 2, 0, height, height};
    }
    // SDL_DestroyTexture(renderTarget);
    // renderTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    //Logger::log("Resize to " + std::to_string(width) + "x" + std::to_string(height));
}


void Game::clean() const {
    SDL_DestroyTexture(renderTarget);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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

SDL_Window* Game::getWindow() const {
    return window;
}
