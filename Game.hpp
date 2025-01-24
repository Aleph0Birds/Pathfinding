//
// Created by wuqiu on 23/1/2025.
//

#ifndef GAME_H
#define GAME_H
#include <SDL_video.h>
#include <SDL_render.h>

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void startLoop();
    void setDeltaTime(uint32_t deltaTimeMs);

private:
    void handleEvents();
    void update(uint32_t deltaTimeMs);
    void render();
    void clean() const;
    void checkUpdate();
    //void tick();

    SDL_Renderer* renderer;
    SDL_Window* window;
    bool isRunning;
    uint32_t deltaTimeMs;
    uint32_t lastUpdateTick;
};

#endif //GAME_H
