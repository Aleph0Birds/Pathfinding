#include "InputHandler.hpp"

#include "KeyMap.hpp"
#include "../Game.hpp"

InputHandler::InputHandler(Game* game) {
    curKeyboardState = SDL_GetKeyboardState(nullptr);
    prevKeyboardState = new Uint8[SDL_NUM_SCANCODES];
    this->game = game;
}

void InputHandler::updateInput() {
    curKeyboardState = SDL_GetKeyboardState(nullptr);
    if (curKeyboardState[KeyMap::PAUSE] && !prevKeyboardState[KeyMap::PAUSE]) {
        if (game->isPaused()) game->resume();
        else game->pause();
    }
    std::copy(curKeyboardState, curKeyboardState + SDL_NUM_SCANCODES, prevKeyboardState);
}
