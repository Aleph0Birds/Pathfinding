#include "KeyMap.hpp"

std::map<SDL_Scancode, KeyAction> KeyMap::keyMap;

void KeyMap::triggerKey(const Uint8 *curKeyboardState, const Uint8 *prevKeyboardState) {
    for (const auto& [key, action] : keyMap) {
        if (action.condition == KEY_PRESSED &&
            curKeyboardState[key] && !prevKeyboardState[key]) {
            action.action();
            } else if (action.condition == KEY_RELEASED &&
                       !curKeyboardState[key] && prevKeyboardState[key]) {
                action.action();
                       } else if (action.condition == KEY_HELD && curKeyboardState[key]) {
                           action.action();
                       }
    }
}