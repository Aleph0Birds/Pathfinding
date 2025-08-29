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

    KeyMap::triggerKey(curKeyboardState, prevKeyboardState);

    std::copy(curKeyboardState, curKeyboardState + SDL_NUM_SCANCODES, prevKeyboardState);
}
