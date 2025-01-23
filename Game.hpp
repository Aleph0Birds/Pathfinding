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
    void handleEvents();
    void update();
    void render();
    void clean();
    void startLoop();

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool isRunning;
};

#endif //GAME_H
