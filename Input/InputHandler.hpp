//
// Created by User on 2025/2/3.
//

#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP
#include <list>
#include <SDL_events.h>


class Game;

class InputHandler {
public:
    explicit InputHandler(Game* game);
    void updateInput();
private:
    const Uint8 *curKeyboardState;
    Uint8 *prevKeyboardState;
    Game* game;
};


#endif //INPUTHANDLER_HPP