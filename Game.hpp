//
// Created by wuqiu on 23/1/2025.
//

#ifndef GAME_H
#define GAME_H
#include <SDL_events.h>
#include <SDL_video.h>
#include <SDL_render.h>
#include <utility>

#include "Algo/PathfindAlgo.hpp"
#include "Input/InputHandler.hpp"
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
    void setTargetFps(unsigned short targetFps);

    void render();

    void setGrid(uint8_t width, uint8_t height);
    void handleResize(int width, int height);
    void pause() { paused = true; }
    void resume() { paused = false; }
    void initDefaultKeyMap();

    std::pair<int, int> getDimensions() const;
    SDL_Renderer* getRenderer() const;
    SDL_Window* getWindow() const;
    constexpr bool isPaused() const { return paused; }
    static constexpr int worldSizeX = 900;
    static constexpr int worldSizeY = 900;
    static constexpr SDL_Rect worldRect = {0, 0, worldSizeX, worldSizeY};

private:
    void handleEvents();
    void preUpdate();
    void update(uint32_t deltaTimeMs);
    void checkRender();
    void clean() const;
    void checkUpdate();
    void handleWindowEvents(const SDL_Event* event);
    //void tick();

    float scale;

    SDL_Rect worldRectCentered;
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* renderTarget;

    InputHandler* inputHandler;

    Grid* grid;
    PathfindAlgo* algo;

    std::pair<int, int> windowDimensions;

    bool isRunning;
    bool paused;
    uint32_t deltaTimeMs;
    uint32_t lastUpdateTickMs;

    uint32_t lastRenderTickMs;
    uint32_t cumulativeRenderTickMs;
    unsigned short fpsCalculated;
    unsigned short targetFps;
    unsigned short targetMsElapsed;
};

#endif //GAME_H
