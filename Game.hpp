//
// Created by wuqiu on 23/1/2025.
//

#ifndef GAME_H
#define GAME_H
#include <SDL_events.h>
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
    void handleResize(int width, int height);

    std::pair<int, int> getDimensions() const;
    SDL_Renderer* getRenderer() const;
    SDL_Window* getWindow() const;
    static constexpr int worldSizeX = 900;
    static constexpr int worldSizeY = 900;
    static constexpr SDL_Rect worldRect = {0, 0, worldSizeX, worldSizeY};

private:
    void handleEvents();
    void update(uint32_t deltaTimeMs);
    void render() const;
    void clean() const;
    void checkUpdate();
    void handleWindowEvents(const SDL_Event* event);
    //void tick();

    float scale;

    SDL_Rect worldRectCentered;
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* renderTarget;
    Grid* grid;

    std::pair<int, int> windowDimensions;

    bool isRunning;
    uint32_t deltaTimeMs;
    uint32_t lastUpdateTick;
};

#endif //GAME_H
