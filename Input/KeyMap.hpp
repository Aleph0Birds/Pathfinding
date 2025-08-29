//
// Created by User on 2025/2/3.
//

#ifndef KEYMAP_HPP
#define KEYMAP_HPP
#include <map>
#include <SDL_scancode.h>

#include "KeyAction.hpp"

class KeyMap {
public:
    static constexpr SDL_Scancode PAUSE = SDL_SCANCODE_SPACE;
    static constexpr SDL_Scancode UP = SDL_SCANCODE_W;
    static constexpr SDL_Scancode DOWN = SDL_SCANCODE_S;
    static constexpr SDL_Scancode RESTART = SDL_SCANCODE_R;

    static void bindKeyFn(const SDL_Scancode key, const KeyAction keyAction) {
        keyMap[key] = keyAction;
    }

    static void bindKeyFn(
        const SDL_Scancode key,
        const KeyCondition condition,
        const std::function<void()>& action)
    {
        keyMap[key] = {condition, action};
    }

    static void triggerKey(const Uint8 *curKeyboardState, const Uint8 *prevKeyboardState);

    static void initKeyMap() {
        keyMap = {};
    }

private:
    static std::map<SDL_Scancode, KeyAction> keyMap;

};

#endif //KEYMAP_HPP
