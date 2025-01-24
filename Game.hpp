//
// Created by wuqiu on 23/1/2025.
//

#ifndef GAME_H
#define GAME_H
#include <SDL_video.h>
#include <SDL_render.h>
#include <utility>

#include "Map/Grid.hpp"

class Game {
public:
    Game();
    ~Game();

    void init(
        const char* title,
        int xpos,
        int ypos,
        int width,
        int height,
        bool fullscreen
        );
    void startLoop();
    void setDeltaTime(uint32_t deltaTimeMs);
    void setGrid(uint8_t width, uint8_t height);
    std::pair<int, int> getDimensions() const;
    SDL_Renderer* getRenderer() const;

private:
    void handleEvents();
    void update(uint32_t deltaTimeMs);
    void render();
    void clean() const;
    void checkUpdate();
    //void tick();

    SDL_Renderer* renderer;
    SDL_Window* window;
    Grid* grid;

    std::pair<int, int> windowDimensions;

    bool isRunning;
    uint32_t deltaTimeMs;
    uint32_t lastUpdateTick;
};

#endif //GAME_H
